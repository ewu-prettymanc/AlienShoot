#include "image_bank_display.h"



image_bank_display::image_bank_display(char * fileroot, 
				       char * ext,
				       int num_frames)
{
  _ib = new image_bank(fileroot, ext, num_frames);
  assert(_ib);

  _src = _ib->get_src();
}

image_bank_display::~image_bank_display()
{
  delete _ib;
}


void image_bank_display::draw(SDL_Surface * screen, 
			      SDL_Rect dest)
{
  SDL_BlitSurface(_ib->get_image(_current_img), &_src,
		  screen, &dest);

}

void image_bank_display::set_image(int img)
{
  assert( img >= 0 && img < _ib->get_num_images() );

  _current_img = img;
}
