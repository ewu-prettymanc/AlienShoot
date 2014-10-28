#ifndef __IMAGE_BANK_H__
#define __IMAGE_BANK_H__

#include "image.h"

using namespace std;

class image_bank
{
 public:

  image_bank(char *filename);
  image_bank(char *fileroot, char* ext, int num_frames);
  virtual ~image_bank();
  
  SDL_Surface * get_image(int i);

  int get_num_images() { return _num_images; }
  SDL_Rect get_src() { return _src; }

 protected:

  SDL_Surface  ** _images;
  int _num_images;
  SDL_Rect _src;
			  
};

#endif
