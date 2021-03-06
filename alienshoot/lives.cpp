#include "lives.h"

lives::lives( char * fontname, int size, SDL_Rect bounds)
  : score(fontname, size )
{
  _bounds = bounds; 
}

lives::~lives()
{

}


void lives::draw( SDL_Surface * screen )
{
  SDL_Rect src, dest;
  SDL_Surface * txt;
  ostringstream oss;

  oss<<"Lives: "<<_score;

  if( _score == 2 )
    {
      _color.r = 255; 
      _color.b = 50; 
      _color.g = 0;
    }

  if( _score == 1 )
    {
      _color.r = 255; 
      _color.b = 0; 
      _color.g = 0; 
    }
  
  
  txt = TTF_RenderText_Blended(_font, oss.str().c_str(), _color );
  assert(txt);

  src.x = 0; 
  src.y = 0;
  src.w = txt->w;
  src.h = txt->h;

  dest = src;
  dest.x = (_bounds.x + _bounds.w) - txt->w;
  
  SDL_BlitSurface(txt, &src, screen, &dest);

  SDL_FreeSurface(txt);
}

int lives::get_lives()
{
  return _score;
}
