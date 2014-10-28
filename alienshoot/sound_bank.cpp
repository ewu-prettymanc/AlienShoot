#include "sound_bank.h" 

#include<iostream>
#include<sstream>
#include<assert.h>
using namespace std;

sound_bank::sound_bank(char *fileroot, char * ext, 
		       int num_sounds)
{
  int i;

  _num_sounds = num_sounds;
  
  _sounds = new Mix_Chunk *[num_sounds];
  assert(_sounds);
  
  for ( i = 0; i < _num_sounds; i ++ )
  {
    ostringstream oss;
    
    oss<<fileroot<<i<<ext;
    
    _sounds[i] = Mix_LoadWAV( (char*) oss.str().c_str());
    
    _sounds[i] = Mix_LoadWAV( (char*) oss.str().c_str());
    if ( ! _sounds[i] )
    {
      cerr<<"Could not load..."<<Mix_GetError()<<endl;
      cerr<<oss.str().c_str()<<endl;
      exit(1);
    }
  }
}

sound_bank::~sound_bank()
{
  int i;

  for ( i = 0; i < _num_sounds; i ++ )
    Mix_FreeChunk(_sounds[i]);
}

void sound_bank::play_random_sound()
{
  int num = rand() % _num_sounds;
  Mix_PlayChannel(-1, _sounds[num], 0);
}
