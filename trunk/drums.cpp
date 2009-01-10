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

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cmath>

#include "display.h"
#include "sound.h"

using namespace std;

extern float drum_values[];
Sound sound;
Display display;

void drum_hit(int which){
  drum_values[which] = 0.5f;
  sound.play_sound(which);
}

int main(){
  if (SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0){
    cout << "Something messed up. :(" <<endl;
    exit(1);
  }

  atexit(SDL_Quit);
    
  //here I assume you have the joystick at 0,
  //if not replace it with a different number
  SDL_Joystick * joystick = SDL_JoystickOpen(0);

  if (joystick == NULL){
    cout <<"Failed to load joystick!" <<endl;
  }else{
    cout <<SDL_JoystickName(0) <<" loaded." <<endl;
    
    //make it so that events are triggered for joysticks
    SDL_JoystickEventState(SDL_ENABLE);
  }
    
  if (!sound.initialize()){
    cout <<"Sound initialization error:" <<sound.get_error()
         <<endl;
    exit(1);
  }

  display.initialize(800, 600, 32, SDL_HWSURFACE | SDL_OPENGL | SDL_GL_DOUBLEBUFFER);

  SDL_Event evt;
  bool loop = true;
  unsigned int last_draw = 0;

  int drum_map[] = {2, 3, 0, 1, 4};

  while (loop){
    while (SDL_PollEvent(&evt)){ //check for event
      if (evt.type == SDL_QUIT){
        //close button, quit
        loop = false;
      }else if (evt.type == SDL_JOYBUTTONDOWN){
        //joystick button hit, let's play
        if (evt.jbutton.button == 4) //pedal
          drum_hit(4);
        else if (evt.jbutton.button < 4)
          drum_hit(evt.jbutton.button);
      }else if (evt.type == SDL_KEYDOWN){
        switch(evt.key.keysym.sym){
        case SDLK_1:
        case SDLK_2:
        case SDLK_3:
        case SDLK_4:
        case SDLK_5:
          drum_hit(drum_map[evt.key.keysym.sym - SDLK_1]);
          break;
        default:
          break;
        }
      }
    }

    if (last_draw < SDL_GetTicks() - 33){
      display.render();
      last_draw = SDL_GetTicks();
    }
    SDL_Delay(1);
  }

  // remember to use the same number here
  //as you did with SDL_JoystickOpen()
  if (joystick)
    SDL_JoystickClose(0);
}
