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

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cmath>

using namespace std;

float drum_values[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
GLUquadricObj * quad = NULL;

Mix_Chunk * sounds[5];
const char * waves[] = {"bass.wav", "crash.wav", "snare.wav",
  "hihat.wav", "kick.wav"};

const float dist = 0.99f;
const float big_radius = 0.7f;

const float light_colours[][4] = {
  {0.5f, 0.5f, 0.5f, 1.0f},
  {1.0f, 1.0f, 1.0f, 1.0f},
  {0.0f, 0.0f, 2.0f, 1.0f}
};

float objects[][5] = {
  { big_radius, dist, 0.0f, 0.0f, 1.0f },
  { dist + big_radius, 0.0f, 0.0f, 0.6f, 0.0f },
  { -dist - big_radius, 0.0f, 1.0f, 0.0f, 0.0f },
  { -big_radius, dist, 1.0f, 1.0f, 0.0f }
};

void drum_hit(int which){
  drum_values[which] = 0.5f;
  Mix_PlayChannel(-1, sounds[which], 0);
}

void render(){
  glClearColor(drum_values[4] * 0.5, drum_values[4] * 0.3, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef(0.05f * sin(4.0f * 3.14f * drum_values[4]), 0.0f, -6.0f);
  glRotatef(-20.0f, 1.0f, 0.0f, 0.0f);

  for (int i = 0; i < 4; i++){
    glTranslatef(objects[i][0], objects[i][1], -drum_values[i]);
    glColor3fv(&objects[i][2]);
    gluDisk(quad, 0.5f, 0.7f, 32, 32);
    glTranslatef(-objects[i][0], -objects[i][1], drum_values[i]);
  }

  for (int i = 0; i < 5; i++){
    if (drum_values[i] > 0.1f)
      drum_values[i] -= 0.1f;
    else
      drum_values[i] = 0.0f;
  }

  SDL_GL_SwapBuffers();
}

void resize(int w, int h){
  if (h == 0) h = 1;

  glViewport(0, 0, (GLsizei)w, (GLsizei)h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void initGL(int w, int h){
  glShadeModel(GL_SMOOTH);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  resize(w,h);

  quad = gluNewQuadric();
  gluQuadricNormals(quad, GLU_SMOOTH);
  
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);

  glLightfv(GL_LIGHT1, GL_AMBIENT, light_colours[0]);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light_colours[1]);
  glLightfv(GL_LIGHT1, GL_POSITION, light_colours[2]);
  glEnable(GL_LIGHT1);
}

int main(){
  if (SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0){
    cout << "Something messed up. :(" <<endl;
    exit(1);
  }

  atexit(SDL_Quit);
    
  //here I assume you have the joystick at 0,
  //if not replace it with a different number
  SDL_Joystick * joystick = SDL_JoystickOpen(0);

  if (joystick == NULL){
    cout <<"Failed to load joystick!" <<endl;
    exit(1);
  }else{
    cout <<SDL_JoystickName(0) <<" loaded." <<endl;
    
    //make it so that events are triggered for joysticks
    SDL_JoystickEventState(SDL_ENABLE);
  }
    
  if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 512) != 0){
    cout <<"Couldn't open audio device: " <<Mix_GetError()
         <<endl;
    exit(1);
  }

  for (int i = 0; i < 5; i++){
    sounds[i] = Mix_LoadWAV(waves[i]);

    if (sounds[i] == NULL)
      cout <<"Loading sound " <<waves[i] <<" failed:"
           <<Mix_GetError() <<endl;
  }

  SDL_Surface * window = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_OPENGL | SDL_GL_DOUBLEBUFFER);

  initGL(800, 600);

  SDL_Event evt;
  bool loop = true;
  int last_btn = 0;
  int last_draw = 0;

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
        }
      }
    }

    if (last_draw < SDL_GetTicks() - 33){
      render();
      last_draw = SDL_GetTicks();
    }
    SDL_Delay(1);
  }

  for (int i = 0; i < 5; i++)
    Mix_FreeChunk(sounds[i]);
  Mix_CloseAudio();

  // remember to use the same number here
  //as you did with SDL_JoystickOpen()
  SDL_JoystickClose(0);

  if (quad)
    gluDeleteQuadric(quad);
}
