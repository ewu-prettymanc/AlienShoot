#include "sprite_array.h"

sprite_array::sprite_array(int size)
{
  _max_size = size;

  _img = new sprite*[size];
  assert(_img);

  _curr_size = 0;
}

sprite_array::~sprite_array()
{
  int i;

  for ( i = 0; i < _curr_size; i ++ )
    delete _img[i];

  delete [] _img;
}

void sprite_array::add(sprite *s)
{
  if ( _curr_size == _max_size )
    grow();

  _img[_curr_size++] = s;
}

void sprite_array::grow()
{
  int newsize = 3 * _max_size / 2;
  int i;
  sprite ** newguy = new sprite*[newsize];

  assert(newguy);

  for ( i = 0; i < _curr_size; i ++ )
    newguy[i] = _img[i];

  delete [] _img;

  _img = newguy;

  _max_size = newsize;
}

void sprite_array::kill(sprite *s)
{
  int index;

  for ( index = 0; index < _curr_size; index ++ )
    if ( _img[index] == s )
    {
      kill(index);
      return;
    }
}

void sprite_array::kill(int i)
{
  assert( i >= 0 && i < _curr_size );

  delete _img[i];

  _img[i] = _img[_curr_size-1];

  _curr_size--;
}

int sprite_array::get_curr_size()
{
  return _curr_size;
}

int sprite_array::collide(sprite *s)
{
  int index;

  for ( index = 0; index < _curr_size; index ++ )
    if ( s->collide( _img[index] ) )
      return index;

  return -1;
}

void sprite_array::draw(SDL_Surface * screen)
{
   int index;

  for ( index = 0; index < _curr_size; index ++ )
    _img[index]->draw(screen);
}

sprite * sprite_array::get_sprite(int which)
{
  assert(which >= 0 && which < _curr_size);

  return _img[which];
}

void sprite_array::move()
{
  int i;
  for ( i = 0; i < _curr_size; i ++ )
    _img[i]->move();
}


void sprite_array::clear()
{
  int i;

  for ( i = 0; i < _curr_size; i ++ )
    delete _img[i];

  _curr_size = 0;
}
