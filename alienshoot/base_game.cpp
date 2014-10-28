#include "base_game.h"

base_game::base_game(char *back, int width, int height)
{
  if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE | SDL_INIT_AUDIO) )
  {
    cerr<<"Could not init sdl: "<<SDL_GetError()<<endl;
    exit(1);
  }

  _screen = SDL_SetVideoMode(width, height, 0,0);

  if ( ! _screen )
  {
    cerr<<"Could not init video mode: "<<SDL_GetError()<<endl;
    exit(1);
  }

  if (TTF_Init() ) 
  {
    cout<<"TTF_Init: "<<TTF_GetError()<<endl;
    exit(1);
  }

  if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) )
  {
    cerr<<"Error initializing SDL_mixer: "<< Mix_GetError()<<endl;
    exit(1);
  }

  _back = new image( back );
  assert(_back);
  
  _back->set_xy(0,0,0);

  _done_mutex = SDL_CreateMutex();
  assert(_done_mutex);
  _data_mutex = SDL_CreateMutex();
  assert(_data_mutex);

  _dummy.type = SDL_QUIT;
}

base_game::~base_game()
{
  delete _back;
  Mix_CloseAudio();
  TTF_Quit();
  SDL_DestroyMutex(_done_mutex);
  SDL_DestroyMutex(_data_mutex);
  SDL_Quit();
}

int run_events(void * data)
{
  base_game * g = (base_game*) data;

  g->event_loop();

  return 1;
}

int run_draw(void * data)
{
  base_game * g = (base_game*) data;
  
  g->draw_loop();
  
  return 1;
}

void base_game::play_game()
{
  _done = 0;

  set_up();
  
  SDL_Thread * event, * draw;
  int status;

  event = SDL_CreateThread(run_events,(void*) this   );
  assert(event);
  draw = SDL_CreateThread(run_draw,(void*) this  );
  assert(draw);

  SDL_WaitThread(event, &status);
  SDL_WaitThread(draw, &status);

}

void base_game::handle_events()
{
  if ( _event.type == SDL_QUIT )
    done();
}


void base_game::draw()
{
  _back->draw(_screen);
}

void base_game::event_loop()
{
  while ( SDL_WaitEvent(&_event) && ! are_we_done() )
  {
    SDL_mutexP(_data_mutex);
    handle_events();
    SDL_mutexV(_data_mutex);
  }
}

void base_game::draw_loop()
{
  while( ! are_we_done() )
  {
    SDL_mutexP(_data_mutex);
    handle_collisions();
    draw();
    SDL_mutexV(_data_mutex);

    SDL_UpdateRect(_screen,0,0,0,0);
    SDL_Delay(FRAME_RATE);
  }
}
  
int base_game::are_we_done()
{
  int result;
  SDL_mutexP(_done_mutex);
  result = _done;
  SDL_mutexV(_done_mutex);

  return result;
}

void base_game::done()
{
  SDL_mutexP(_done_mutex);
  _done = 1;
  SDL_mutexV(_done_mutex);

  SDL_PushEvent(&_dummy);
}
