#include "bullet_array.h"

bullet_array::bullet_array( char * fileroot, char * ext, 
			    int frames,  SDL_Rect bounds , gunner * gun,
			    sound_bank * shot_sound, 
			    sound_bank * pop_sound ) 
  : sprite_array(), _bounds( bounds ), _gunner(gun),
    _shot_sound( shot_sound ), _pop_sound( pop_sound) 
{
  _disp = new image_bank_display( fileroot, ext, frames ); 
  assert( _disp ); 

  _fire_rate = FIRE_RATE;
  _fire = 0; 
  _time = 0;
}

 
bullet_array::~bullet_array()
{
  delete _disp; 
} 

void bullet_array::shoot()
{
  int x, y;

  bounded_sprite * b = new bounded_sprite( _disp, _bounds ); 
  assert( b ); 
  
  _shot_sound->play_random_sound();

  x = _gunner->get_x(); 
  y = _gunner->get_y(); 
  
  b->set_xy(x,y); 
  b->set_dxdy(0, BULLET_SPEED ); 
  
  add( b ); 
}

void bullet_array::set_fire(int on_off )
{
  _fire = on_off; // set it to auto fire or not
}

void bullet_array::draw( SDL_Surface * screen )
{
  if( _fire )// shoot a new bullet if the fire is turned on
    {
      _time ++; 
      if( _time == _fire_rate )
	{
	  shoot(); // spawn a new bullet
	  _time = 0; 
	}
    }

  sprite_array::draw(screen); 
  
} 

int bullet_array::hit_alien( alien_array * aliens )
{
  int i, j; 
  int   num_shot = 0; 
  
  for( i=0; i < _curr_size; i++)
    {
       j = aliens->collide( _img[i] ); 
      
      if( j >=0 ) // it collided
	{
	  _pop_sound->play_random_sound();
	  kill( i ); 
	  aliens->kill( j ); 
	  i--; 
	  
	  num_shot ++;
	}
    }
  
  return num_shot; 
}
 
void bullet_array::remove_bad_shot()
{
  bounded_sprite * b; 
  int i; 
  
  for( i=0; i < +_curr_size; i ++ )
    {
      b = (bounded_sprite * ) _img[i]; 
      if( b->past_top_bound() )
	{
	  kill( i ); 
	  i --; 
	}
    }
} 

