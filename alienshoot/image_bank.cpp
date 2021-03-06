#include "image_bank.h"
#include<sstream> 


image_bank::image_bank(char *filename)
{
  _images = new SDL_Surface*[1];
  assert(_images);

  _images[0] = IMG_Load(filename);
  assert(_images[0]);
  _num_images = 1;

  SDL_Surface * img = _images[0];

  _src.x = 0;
  _src.y = 0;
  _src.h = img->h;
  _src.w = img->w;

}

image_bank::image_bank(char *fileroot, char* ext, int num_frames)
{
  int i;
  _images = new SDL_Surface*[num_frames];
  assert(_images);
  
  for ( i = 0; i < num_frames; i ++ )
  {
    ostringstream filename;

    filename<<fileroot<<i<<ext;

    _images[i] = IMG_Load((char*)  filename.str().c_str() );
    
    if( ! _images[i] )
      {
	cerr<<"failed to load image "<<(char*)  filename.str().c_str()<<endl;
	exit(1); 
      }
    assert(_images[i]);
  }


  _num_images = num_frames;

  SDL_Surface * img = _images[0];

  _src.x = 0;
  _src.y = 0;
  _src.h = img->h;
  _src.w = img->w;
}


image_bank::~image_bank()
{
  int i;

  for ( i = 0; i < _num_images; i ++ )
    SDL_FreeSurface(_images[i]);
  
  delete [] _images;
}

SDL_Surface * image_bank::get_image(int i)
{
  assert(i >= 0 && i < _num_images );

  return _images[i];
}



  
