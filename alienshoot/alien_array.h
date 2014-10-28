#ifndef __ALIEN_ARRAY_H__
#define __ALIEN_ARRAY_H__

#include "sprite_array.h"
#include "bounded_sprite.h"
#include "image_bank_display.h"
#include "gamedata.h"
#include "bounded_alien.h"
#include "gunner.h"
#include "sound_bank.h"


class alien_array : public sprite_array
{
 public:

  alien_array(char *fileroot, char *ext, int frames, double spawn_rate, 
	      SDL_Rect bounds, sound_bank * spawn_sound, 
	      sound_bank * hit_sound );
  ~alien_array();

  virtual void spawn_aliens(int howmany);
  virtual void draw(SDL_Surface * screen);
  virtual int at_edge();
  virtual int hit(int x, int y);
  virtual int hit_gunner( sprite * peter ); 
  virtual void clear();

 protected:

  image_bank_display * _disp;
  SDL_Rect _bounds;

  int _time; 
  int _num_spawned; 
  int _spawn_rate; 
  int _alien_init;
  int _rand_max;
  int _rand_min; 
  sound_bank * _spawn_sound;
  sound_bank * _hit_sound;
};


#endif
