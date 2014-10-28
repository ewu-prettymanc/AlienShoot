#include"image.h"


// 	name: constructor
// 	desc: opens an image from a given file
// 	params: char * filename
// 	return: n/a
// 	1) call image load
// 	2) check for success
// 	3) set up the src and dest rectangles
image::image(char * filename)
{
  _img = IMG_Load(filename);
 
  //cerr<<"calling image constructor."<<endl;
 
  if ( ! _img )
  {
    cerr<<"Could not load "<<filename<<endl;
    cerr<<IMG_GetError()<<endl;
    exit(1);
  }

  _src.x = _src.y = 0;
  _src.w = _img->w;
  _src.h = _img->h;

  _dest = _src;
}

// 	name: destructor
// 	desc: free's the _img
// 	params: none
// 	return: n/a
// 	1) call SDL_FreeSurface on _img
image::~image()
{
  //cerr<<"calling image destructor."<<endl;
  SDL_FreeSurface(_img);
}

// 	name: print
// 	desc: used for debugging
// 	params: none
// 	return: void
// 	1) print the address of the surface
// 	2) print each member of src
// 	3) print each member of dest
void image::print()
{
  cout<<"debugging an image..."<<endl;
  cout<<"_img: "<<_img<<endl;
  cout<<"_src.x: "<<_src.x<<" _src.y: "<<_src.y
      <<" _src.w: "<<_src.w<<" _src.h: "<<_src.h<<endl;
  cout<<"_dest.x: "<<_dest.x<<" _dest.y: "<<_dest.y
      <<" _dest.w: "<<_dest.w<<" _dest.h: "<<_dest.h<<endl;
}

// 	name: draw
// 	desc: draws the image on the screen
// 	params: SDL_Surface * screen
// 	return: void
//	1) call SDL_BlitSurface
void image::draw(SDL_Surface * screen)
{
  //cerr<<"calling image's draw"<<endl;
  SDL_BlitSurface(_img, &_src, screen, &_dest);
}

// 	name: set_xy
// 	desc: sets the dest.x and dest.y
// 	params: int x, int y, int center=1
// 	return: void
// 	1) set dest.x and dest.y to x and y
// 	2) if center, then subtract half of width from dest.x
// 	   and subtract half of height to dest.y
void image::set_xy(int x, int y, int center)
{
  _dest.x = x;
  _dest.y = y;
  
  if ( center )
  {
    _dest.x -= _dest.w/2;
    _dest.y -= _dest.h/2;
  }
}



int image::collide(image *i)
{
  if ( my_corners_in_you(i) || i->my_corners_in_you(this) )
    return 1;

  return 0;
}

int image::check_point(int x, int y)
{
  if ( x < _dest.x || x > _dest.x + _dest.w )
    return 0;

  if ( y < _dest.y || y > _dest.y + _dest.h )
    return 0;

  return 1;
}

int image::my_corners_in_you(image * i)
{
  if ( i->check_point(_dest.x, _dest.y) ||
       i->check_point(_dest.x + _dest.w, _dest.y) ||
       i->check_point(_dest.x, _dest.y + _dest.h ) ||
       i->check_point(_dest.x + _dest.w, _dest.y + _dest.h ) )
    return 1;

  return 0;
}



int image::get_centerx()
{
  return _dest.x + _dest.w / 2;
}

int image::get_centery()
{
  return _dest.y + _dest.h / 2;
}

int image::get_width()
{
  return _dest.w;
}

int image::get_height()
{
  return _dest.h;
}

SDL_Surface * image::get_image()
{
  return _img;
}
