#ifndef __BOUNDED_SPRITE_H__
#define __BOUNDED_SPRITE_H__

#include "sprite.h"

class bounded_sprite : public sprite
{
public:

  bounded_sprite(display_manager * dm, SDL_Rect bounds);
  ~bounded_sprite();

  virtual void set_bounds(SDL_Rect bounds);
  
  virtual void move();
  
  virtual int at_edge();
  virtual int past_top_bound();
  
protected:

  virtual void hit_left_bound();
  virtual void hit_right_bound();
  virtual void hit_bottom_bound();
  virtual void hit_top_bound();

  SDL_Rect _bounds;
  
};



#endif
