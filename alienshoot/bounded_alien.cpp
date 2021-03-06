#include "bounded_alien.h"

bounded_alien::bounded_alien( display_manager * dm , SDL_Rect bounds )
  : bounded_sprite( dm, bounds)
{
}

bounded_alien::~bounded_alien( )
{
}

void bounded_alien::move()
{
  sprite::move();

  if ( _dest.x < _bounds.x )  // moved off the left hand side
    hit_left_bound();

  if ( _dest.y < _bounds.y ) // top
    hit_top_bound();

  if ( _dest.x + _dest.w > _bounds.x + _bounds.w ) // right
    hit_right_bound();

  if ( _dest.y > _bounds.y + _bounds.h ) // bottom
    hit_bottom_bound();

}

void bounded_alien::hit_top_bound()
{
  // don't do anything..they are heading down. Just keep
  // its dy will always be negative
}

void bounded_alien::hit_bottom_bound()
{
  _dest.y = _bounds.y - _dest.h; // resets it to the top of the screen 
}
