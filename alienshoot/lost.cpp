#include "lost.h"


lost::lost( char * fontname, int size , SDL_Rect b )
  : score( fontname, size ), _bounds( b )
{
  
}

lost::~lost()
{

}

void lost::draw( SDL_Surface * screen )
{
  SDL_Rect src, dest;
  SDL_Surface * txt;
  ostringstream oss;

  oss<<"DEATH BY FART!! ";


  txt = TTF_RenderText_Blended(_font, oss.str().c_str(), _color);
  assert(txt);

  src.x = 0;
  src.y = 0;
  src.w = txt->w;
  src.h = txt->h;

  dest = src;
  dest.x = (_bounds.x + _bounds.w - txt->w )/2; // center on x
  dest.y = (_bounds.y + _bounds.h - txt->h)/2; // center on y
  
  SDL_BlitSurface(txt, &src, screen, &dest);

  SDL_FreeSurface(txt);
}
