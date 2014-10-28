
#include "sprite.h"

sprite::sprite(display_manager *dm)
{
  _dx = _dy = 0;

  _dm = dm;

  _dest = dm->get_src();

  _current = 0;
}


sprite::~sprite()
{

}

void sprite::set_dxdy(int dx, int dy)
{
  _dx = dx;
  _dy = dy;
}

void sprite::set_dx(int amt)
{
  _dx = amt;
}

void sprite::move()
{
  _dest.x += _dx;
  _dest.y += _dy;
}

void sprite::draw(SDL_Surface * screen)
{
  _current ++;
  
  if ( _current >= _dm->get_num_images() )
    _current = 0;
  
  _dm->set_image(_current);

  _dm->draw(screen, _dest);
}


void sprite::inc_dx(int amt)
{
  _dx += amt;
}

void sprite::inc_dy(int amt)
{
  _dy += amt;
}


int sprite::get_dx()
{
  return _dx;
}

int sprite::get_dy()
{
  return _dy;
}


int sprite::collide(sprite *i)
{
  if ( my_corners_in_you(i) || i->my_corners_in_you(this) )
    return 1;

  return 0;
}

int sprite::check_point(int x, int y)
{
  if ( x < _dest.x || x > _dest.x + _dest.w )
    return 0;

  if ( y < _dest.y || y > _dest.y + _dest.h )
    return 0;

  return 1;
}

int sprite::my_corners_in_you(sprite * i)
{
  if ( i->check_point(_dest.x, _dest.y) ||
       i->check_point(_dest.x + _dest.w, _dest.y) ||
       i->check_point(_dest.x, _dest.y + _dest.h ) ||
       i->check_point(_dest.x + _dest.w, _dest.y + _dest.h ) )
    return 1;

  return 0;
}



int sprite::get_centerx()
{
  return _dest.x + _dest.w / 2;
}

int sprite::get_centery()
{
  return _dest.y + _dest.h / 2;
}

int sprite::get_width()
{
  return _dest.w;
}

int sprite::get_height()
{
  return _dest.h;
}


// 	name: set_xy
// 	desc: sets the dest.x and dest.y
// 	params: int x, int y, int center=1
// 	return: void
// 	1) set dest.x and dest.y to x and y
// 	2) if center, then subtract half of width from dest.x
// 	   and subtract half of height to dest.y
void sprite::set_xy(int x, int y, int center)
{
  _dest.x = x;
  _dest.y = y;
  
  if ( center )
  {
    _dest.x -= _dest.w/2;
    _dest.y -= _dest.h/2;
  }
}
