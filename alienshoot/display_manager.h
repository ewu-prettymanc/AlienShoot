
#ifndef __DISPLAY_MANAGER_H__
#define __DISPLAY_MANAGER_H__

#include "image.h"

class display_manager
{
 public:
  
  display_manager(){}
  virtual ~display_manager(){}
  
  virtual void draw(SDL_Surface * sreen, SDL_Rect dest)=0;
  
  SDL_Rect get_src() { return _src; }
  virtual void set_image(int amt){}
  virtual int get_num_images() { return 1;}
 protected:

  SDL_Rect _src;
};


#endif
