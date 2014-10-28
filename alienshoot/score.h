#ifndef __SCORE_H__
#define __SCORE_H__

#include "image.h"
#include<SDL_ttf.h>
#include <string>
#include <sstream>

class score
{
 public:

  score(char * fontname, int size);
  ~score();

  virtual void clear(int start);
  virtual void inc_rate(int amt);
  virtual void draw(SDL_Surface * screen);
 protected:

  int _score;
  TTF_Font * _font;
  SDL_Color _color;
};

#endif
