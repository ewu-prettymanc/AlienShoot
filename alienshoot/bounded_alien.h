#ifndef __BOUNDED_ALIEN_H__
#define __BOUNDED_ALIEN_H__

#include "bounded_sprite.h"

class bounded_alien :public bounded_sprite
{
 public: 
  bounded_alien( display_manager * dm, SDL_Rect bounds ); 
  ~bounded_alien(); 
  virtual void  move(); 
  
 protected: 
  virtual void hit_bottom_bound();
  virtual void hit_top_bound();
 
};

#endif
