#ifndef __ALIENSHOOT_H__
#define __ALIENSHOOT_H__


#include<SDL_ttf.h>

#include "base_game.h"
#include "alien_array.h"
#include "score.h"
#include "gamedata.h"
#include "gunner.h"
#include "lives.h"
#include "bullet_array.h"
#include "lost.h"
#include "sound_bank.h"

class alienshoot : public base_game
{
 public:

  alienshoot();
  ~alienshoot();

 protected:

  virtual void handle_events();
  virtual void handle_collisions(); 
  virtual void draw();
  virtual void set_up();
  virtual void reset();
 
  alien_array * _aliens; 
  image_bank_display * _gunner_bank;
  gunner * _gunner; 
  bullet_array * _bullets; 
 
  lost * _lost;
  lives * _lives; 
  score * _score;

  sound_bank * _shot_sound;
  sound_bank * _spawn_sound;
  sound_bank * _hit_sound;
  sound_bank * _lost_sound;
  sound_bank * _pop_sound;
  Mix_Music  * _back_music; 
};

#endif
