#include"score.h"
#include<sstream>

score::score(char * fontname, int size)
{
  _font = TTF_OpenFont(fontname, size);
  assert(_font);
  _score = 0;
  _color.r = 255;
  _color.b = 0;
  _color.g = 255;
}

score::~score()
{
  TTF_CloseFont(_font);
}

void score::clear( int start) 
{
  _score = start;
  _color.r = 255;
  _color.b = 0;
  _color.g = 255;
}

void score::inc_rate(int amt)
{
  _score += amt;
}

void score::draw(SDL_Surface * screen)
{
  SDL_Rect src, dest;
  SDL_Surface * txt;
  ostringstream oss;

  oss<<"Score: "<<_score;

  
  txt = TTF_RenderText_Blended(_font, oss.str().c_str(), _color);
  assert(txt);

  src.x = 0;
  src.y = 0;
  src.w = txt->w;
  src.h = txt->h;

  dest = src;
  
  SDL_BlitSurface(txt, &src, screen, &dest);

  SDL_FreeSurface(txt);
}
