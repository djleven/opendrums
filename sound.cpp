/*
The MIT License

Copyright (c) 2008 Rob Britton

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

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
