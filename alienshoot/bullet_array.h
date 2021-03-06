#ifndef __BULLET_ARRAY_H__
#define __BULLET_ARRAY_H__

#include "alien_array.h"
#include "sprite_array.h"
#include "bounded_sprite.h"
#include "image_bank_display.h"
#include "gamedata.h"
#include "bounded_alien.h"
#include "gunner.h"
#include "sound_bank.h"

class bullet_array : public sprite_array
{
 public: 
  bullet_array( char * fileroot, char * ext, int frames, SDL_Rect bounds, 
		gunner * gun, sound_bank * shot_sound , 
		sound_bank * pop_sound); 
  ~bullet_array(); 
  
  void shoot(); 
  void set_fire(int on_off ); 
  void draw( SDL_Surface * screen ); 

  int hit_alien( alien_array * aliens ); 
  void remove_bad_shot(); 
  
 protected: 
  image_bank_display * _disp; 
  SDL_Rect _bounds; 
  int _fire_rate; 
  gunner * _gunner; 
  int _fire; 
  int _time; 

  sound_bank * _shot_sound;
  sound_bank * _pop_sound;
  
};


#endif
