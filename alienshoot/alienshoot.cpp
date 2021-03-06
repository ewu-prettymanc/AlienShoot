#include "alienshoot.h"

alienshoot::alienshoot()
  : base_game( (char*) BACK, BACK_W, BACK_H) 
{
  SDL_Rect b;
  b.x = 0;
  b.y = 0;
  b.w = _screen->w;
  b.h = _screen->h;

  // allocate the sounds
  _shot_sound = new sound_bank( (char*) SHOT_SOUND, (char*)".wav", SHOT_NUM );
  assert( _shot_sound ); 
  
  _spawn_sound = new sound_bank( (char*)SPAWN_SOUND, 
				   (char*)".wav", SPAWN_NUM); 
  assert( _spawn_sound ); 
 
  _hit_sound = new sound_bank( (char*) HIT_SOUND, (char*)".wav", HIT_NUM ); 
  assert( _hit_sound ); 

  _lost_sound = new sound_bank( (char*) LOST_SOUND, (char*)".wav", LOST_NUM);
  assert( _lost_sound ); 
  
  _pop_sound = new sound_bank( (char*) POP_SOUND, (char*)".wav", POP_NUM );
  assert( _pop_sound ); 
  
  _back_music = Mix_LoadMUS( (char*) BACK_MUSIC );
  assert( _back_music ); 

  // allocate the aliens
  _aliens = new alien_array( (char*) ALIEN1, (char*)".png",
			     ALIEN_NUM, ALIEN_SPAWN_RATE, b, _spawn_sound,
			     _hit_sound);
  assert(_aliens);

  // allocate score data
  _score = new score( (char*) FONT,  SCORE_FONT);
  assert(_score);
  _lives = new lives( (char*) FONT, SCORE_FONT, b); 
  assert( _lives );   
  _lost = new lost( (char*) FONT, SCORE_LOST, b ); 
  assert( _lost ); 
  
  // allocate the gunner
  _gunner_bank = new image_bank_display( (char*) GUNNER, (char*)".png" , 
					 GUNNER_NUM); 
  assert( _gunner_bank ); 
  _gunner = new gunner( _gunner_bank, b); 
  assert ( _gunner );

  // allocate the bullets
  _bullets = new bullet_array( (char * ) BULLET, (char*) ".png",
			   BULLET_NUM, b , _gunner, _shot_sound, _pop_sound); 
  assert( _bullets ); 

}

alienshoot::~alienshoot()
{
  delete _aliens;
  delete _gunner_bank;
  delete _gunner;
  delete _bullets;
  
  delete _lost;
  delete _lives;
  delete _score;

  delete _shot_sound;
  delete _spawn_sound;
  delete _hit_sound;
  delete _lost_sound;
  delete _pop_sound;
  Mix_FreeMusic( _back_music ); 
}


void alienshoot::handle_events()
{
  int inc;

  if ( _event.type == SDL_KEYDOWN )
  {
    if ( _event.key.keysym.sym == SDLK_ESCAPE ||
	 _event.key.keysym.sym == SDLK_q )
    {
      done();
      return;
    }
    
    if( _event.key.keysym.sym == SDLK_RIGHT )
      _gunner->move(GUNNER_SPEED );// gunner move left 
    
    if( _event.key.keysym.sym == SDLK_LEFT )
      _gunner->move( -1*GUNNER_SPEED ); // gunner move right
    
    if( _event.key.keysym.sym == SDLK_SPACE )
      {
	_bullets->shoot();
	_bullets->set_fire( 1 ); // set auto fire
      }

    return;
  }

  if( _event.type == SDL_KEYUP )
    {
      if( _event.key.keysym.sym == SDLK_RIGHT ||
	  _event.key.keysym.sym == SDLK_LEFT )
	_gunner->move( 0 ); // stop the gunner moving

      if( _event.key.keysym.sym == SDLK_SPACE )
	_bullets->set_fire( 0 ); // key is up...turn auto fire off
      
      return; 
    }

  if ( _event.type == SDL_MOUSEBUTTONDOWN )
  {
    inc = _aliens->hit(_event.button.x, _event.button.y);
    if ( inc > 0 )
      _score->inc_rate(inc);
   
    return;
  }

  base_game::handle_events();
}

void alienshoot::handle_collisions()
{
  int inc; 
  int hit; 

  _aliens->move();
  _gunner->sprite::move(); 

  inc = _bullets->hit_alien( _aliens ); 
  if(inc > 0 ) // count hits
    _score->inc_rate( inc ); 

  _bullets->remove_bad_shot();
  _bullets->move();
  
  hit = _aliens->hit_gunner ( _gunner ); 
   if( hit > 0 )
     {
       _lives->inc_rate( -hit); // subtract off lives
       _score->inc_rate( hit ); 
     }
   
   if( _lives->get_lives() <= 0 )
     {
       reset(); 
       return;
     }
}

void alienshoot::draw()
{
  base_game::draw();
  
  _aliens->draw(_screen);
  _bullets->draw(_screen); 
  _score->draw(_screen);
  _lives->draw( _screen ); 
  _gunner->draw(_screen); 
}

void alienshoot::set_up()
{
  _aliens->spawn_aliens(ALIEN_INIT);
  _score->clear(0);
  _lives->clear( LIVES_INIT );
  
  if( MUSIC_PLAY )
    Mix_PlayMusic( _back_music, -1 ); // play back ground music recursivly 
}


void alienshoot::reset()
{

  _lost_sound->play_random_sound(); //play sound
  _lost->draw(_screen ); // draw lost writing
  SDL_UpdateRect(_screen,0,0,0,0);// update screen

  SDL_Delay( RESET_TIME );// display to user for several seconds
 
  _aliens->clear();
  _bullets->clear();
  _gunner->reset();
  set_up();
}
