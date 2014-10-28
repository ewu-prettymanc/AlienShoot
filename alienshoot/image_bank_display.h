#ifndef __IMAGE_BANK_DISPLAY_H__
#define __IMAGE_BANK_DISPLAY_H__

#include "image_bank.h"
#include "display_manager.h"

class image_bank_display : public display_manager
{
 public:

  image_bank_display(char * fileroot, char * ext,
		     int num_frames);
  virtual ~image_bank_display();

  virtual void draw(SDL_Surface * screen, SDL_Rect dest);

  void set_image(int img);

  int get_num_images() { return _ib->get_num_images();}

 protected:
  
  int _current_img;
  image_bank * _ib;

};


#endif
