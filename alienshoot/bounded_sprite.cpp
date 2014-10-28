#include "bounded_sprite.h"


bounded_sprite::bounded_sprite(display_manager * dm, SDL_Rect bounds)
  : sprite(dm)
{
  _bounds = bounds;
}

bounded_sprite::~bounded_sprite()
{
}

void bounded_sprite::set_bounds(SDL_Rect bounds)
{
  _bounds = bounds;
}

void bounded_sprite::move()
{
  sprite::move();

  if ( _dest.x < _bounds.x )  // moved off the left hand side
    hit_left_bound();

  if ( _dest.y < _bounds.y ) // top
    hit_top_bound();

  if ( _dest.x + _dest.w > _bounds.x + _bounds.w ) // right
    hit_right_bound();

  if ( _dest.y + _dest.h > _bounds.y + _bounds.h ) // bottom
    hit_bottom_bound();

}
// 

void bounded_sprite::hit_left_bound()
{
  _dx *= -1;
}

void bounded_sprite::hit_right_bound()
{
  _dx *= -1;
}

void bounded_sprite::hit_top_bound()
{
  _dy *= -1;
}
void bounded_sprite::hit_bottom_bound()
{
  _dy *= -1;
}

int bounded_sprite::at_edge()
{
  if ( _dest.x <= _bounds.x )
    return 1;
  if ( _dest.x + _dest.w >= _bounds.x + _bounds.w )
    return 1;
  if ( _dest.y <= _bounds.y )
    return 1;
  if ( _dest.y + _dest.h >= _bounds.y + _bounds.h )
    return 1;

  return 0;
}

int bounded_sprite::past_top_bound( )
{
  if( _dest.y  <= _bounds.y )// bottom of the image past the top bound
    return 1; 
  
  return 0; 
}


   
