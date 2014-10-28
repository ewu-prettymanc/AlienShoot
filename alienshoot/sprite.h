#ifndef __SPRITE_H__
#define __SPRITE_H__

#include"display_manager.h"

class sprite
{
 public:

  sprite(display_manager *dm);
  ~sprite();
  
  void set_dxdy(int dx, int dy);
  virtual void move();
  virtual void draw(SDL_Surface * screen);
  
  virtual void inc_dx(int amt);
  virtual void inc_dy(int amt);
  
  virtual void set_dx(int amt);
  
  int get_dx();
  int get_dy();
  
  virtual int collide(sprite *i);
  virtual int check_point(int x, int y);
  
  virtual int get_centerx();
  virtual int get_centery();
  virtual int get_height();
  virtual int get_width();
  virtual void set_xy(int x, int y, int center=1);
  
  
 protected:
  
  
  virtual int my_corners_in_you(sprite * i);

  SDL_Rect _dest;
  int _dx, _dy;
  display_manager * _dm;
  int _current;
  

};



#endif
