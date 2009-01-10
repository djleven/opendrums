#include "sound.h"

#include <cstring>
using namespace std;

// TODO: Make this loaded from a file or something
const char * waves[] = {"bass.wav", "crash.wav", "snare.wav",
  "hihat.wav", "kick.wav"};

Sound::Sound(){
  for (int i = 0; i < 5; i++)
    sounds[i] = NULL;
  memset(last_error, 0, sizeof(char) * 256);
}

Sound::~Sound(){
  for (int i = 0; i < 5; i++)
    if (sounds[i])
      Mix_FreeChunk(sounds[i]);
  Mix_CloseAudio();
}

bool Sound::initialize(){
  if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 512) != 0){
    strcpy(last_error, Mix_GetError());
    return false;
  }

  for (int i = 0; i < 5; i++){
    sounds[i] = Mix_LoadWAV(waves[i]);

    if (sounds[i] == NULL)
      sprintf(last_error, "Loading sound %s failed: %s\n", waves[i], Mix_GetError());
  }
  return true;
}

void Sound::play_sound(int which){
  Mix_PlayChannel(-1, sounds[which], 0);
}
