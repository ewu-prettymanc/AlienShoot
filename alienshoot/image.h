#ifndef __IMAGE_H__
#define __IMAGE_H__

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<assert.h>
#include<stdlib.h>

using namespace std;
// Desc: displays one image 
class image
{
 public:
  
  // 	name: constructor
  // 	desc: opens an image from a given file
  // 	params: char * filename
  // 	return: n/a
  image(char * filename);

  // 	name: destructor
  // 	desc: free's the _img
  // 	params: none
  // 	return: n/a
  virtual ~image();

  // 	name: print
  // 	desc: used for debugging
  // 	params: none
  // 	return: void
  virtual void print();

  // 	name: draw
  // 	desc: draws the image on the screen
  // 	params: SDL_Surface * screen
  // 	return: void
  virtual void draw(SDL_Surface * screen);

  // 	name: set_xy
  // 	desc: sets the dest.x and dest.y
  // 	params: int x, int y, int center=1
  // 	return: void
  virtual void set_xy(int x, int y, int center=1);

  virtual int collide(image *i);
  virtual int check_point(int x, int y);

  virtual int get_centerx();
  virtual int get_centery();
  virtual int get_height();
  virtual int get_width();

  SDL_Surface * get_image();

 protected:

  virtual int my_corners_in_you(image * i);

  SDL_Surface * _img;
  SDL_Rect _src, _dest;  

};


#endif
