#ifndef __SPRITE_ARRAY_H__
#define __SPRITE_ARRAY_H__


#include "sprite.h"

class sprite_array
{
public:

  sprite_array(int size=10);
  ~sprite_array();

  void move();

  sprite * get_sprite(int which);
  virtual void add(sprite * s);
  virtual void kill(sprite *s);
  virtual void kill(int i);

  int get_curr_size();
  
  virtual int collide(sprite * s);
  virtual void draw(SDL_Surface * screen);
  virtual void clear();

 protected:

  void grow();

  sprite ** _img;
  int _max_size, _curr_size;


};


#endif
