#include "alien_array.h"

#include <string.h>
#include "image_bank_display.h"

alien_array::alien_array(char *fileroot, char * ext, 
			 int frames, double spawn_rate, 
			 SDL_Rect bounds, sound_bank * spawn_sound,
			 sound_bank * hit_sound)
  : sprite_array(),  _bounds(bounds), _spawn_sound( spawn_sound ),
    _hit_sound( hit_sound )
{

  _disp = new image_bank_display(fileroot, ext, frames);
  assert(_disp);
  
  _time = 0;
  _num_spawned = 0;
  _spawn_rate = spawn_rate;
  _rand_max = MAX_ALIEN_POS;
  _rand_min = MIN_ALIEN_POS;
  _alien_init = ALIEN_INIT;
}

alien_array::~alien_array()
{
  delete _disp;
}

void alien_array::spawn_aliens(int howmany)
{
  int i, x, y, dy, dx;
  bounded_alien * g;
  
  _spawn_sound->play_random_sound();

  for ( i = 0; i < howmany; i ++ )
  {
    g = new bounded_alien(_disp, _bounds);
    assert(g);
    
    if( _num_spawned % SPAWN_CHANGE_RATE == 0 )//change speed as time progresses
      {
	_rand_max += SPEED_CHANGE_SIZE;
	_rand_min += SPEED_CHANGE_SIZE;
      }

    x = rand() % ( _bounds.w - g->get_width() ) + _bounds.x;
    y = _bounds.y - g->get_height();// spanwn it above the screen  

 
    // if dx travel then generate a value
    if( DX_TRAVEL )
      dx = rand()%(_rand_min)*2 - _rand_min;
    else 
      dx = 0;
    dy = rand()%(_rand_max) + _rand_min; 

    g->set_xy(x,y,0);
    g->set_dxdy(dx, dy);// aliens go straight down

    add(g);
  }
}

void alien_array::draw(SDL_Surface * screen)
{
  sprite_array::draw(screen);
    
  _time++; 
  
  if( _time == _spawn_rate)
    {
      _time = 0;
      spawn_aliens(_alien_init); 
      _num_spawned++; 
      
      // every 'x' amount of spawned aliens
      // decrease the spawn rate 
      // and increase the number spawned
      if( _num_spawned % SPAWN_CHANGE_RATE == 0 &&
	  _spawn_rate - SPAWN_CHANGE_SIZE >= 0 )
	{
	  _spawn_rate-= SPAWN_CHANGE_SIZE; 
	  _alien_init += SPAWN_INIT_CHANGE;
	}
    }
}

int alien_array::at_edge()
{
  int i;
  bounded_sprite * g;

  for ( i = 0; i < _curr_size; i ++ )
  {
    g = (bounded_sprite *) _img[i];

    if ( g->at_edge() )
      return 1;
  }

  return 0;
}

int alien_array::hit(int x, int y)
{
  int i, total = 0;
  
  for ( i = 0; i < _curr_size; i ++ )
    if ( _img[i]->check_point(x,y) )
    {
      kill(i);
      i--;
      total ++;
    }
  return total;
}

int alien_array::hit_gunner( sprite * peter )
{
  int i; 
  int hit = 0;
  
  for( i=0; i<_curr_size; i++ )
    if( peter->collide( _img[i] ) )
      {
	_hit_sound->play_random_sound();
	kill(i); 
	i--; 
	hit++;
      }

  return hit; 
}


void alien_array::clear()
{
  sprite_array::clear();
  _time = 0;
  _num_spawned = 0;
  _spawn_rate = ALIEN_SPAWN_RATE; 
  _rand_max = MAX_ALIEN_POS;
  _rand_min = MIN_ALIEN_POS;
  _alien_init = ALIEN_INIT;
}
