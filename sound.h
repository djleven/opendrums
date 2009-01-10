#ifndef __SOUND_H
#define __SOUND_H

#include <SDL.h>
#include <SDL_mixer.h>

class Sound{
  Mix_Chunk * sounds[5];
  char last_error[256];
public:
  Sound();
  ~Sound();

  bool initialize();
  void play_sound(int which);

  const char * get_error() { return last_error; }
};

#endif

