#include "gunner.h"

gunner::gunner( display_manager * dm, SDL_Rect bounds )
  : bounded_sprite(dm, bounds )
{
  SDL_Rect img = dm->get_src(); 
  
  _defaultx = (_bounds.w + _bounds.x )/2 - img.w/2; // place it in the center
  _defaulty = (_bounds.y + _bounds.h)- img.h; 
  // set it at the bottom of the screen
  
  set_xy( _defaultx, _defaulty, 0); // don't center it
  set_dxdy(0,0); // initially not moving
}

gunner::~gunner()
{
}

void  gunner::move(int howfar)
{
  if( _dest.x + _dest.w < _bounds.x ) // past or hit left edge
    _dest.x = _bounds.x + _bounds.w;// _bounds.x + _bounds.w; 
  
  if( _dest.x > _bounds.x + _bounds.w ) // past or hit right edge
    _dest.x = _bounds.x - _dest.w; 
  
  sprite::set_dxdy( howfar, 0 ); 
}


int gunner::get_y()
{
  return _dest.y; 
}

int gunner::get_x()
{
  return _dest.w/2 + _dest.x; // returns the center x coordinate
}


void gunner::reset()
{
  set_xy( _defaultx, _defaulty, 0); // don't center it
  set_dxdy(0,0); // initially not moving
}
