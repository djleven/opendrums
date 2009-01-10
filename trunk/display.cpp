#include "display.h"

#include <cmath>
using namespace std;

// TODO: make this not global variables
const float light_colours[][4] = {
  {0.5f, 0.5f, 0.5f, 1.0f},
  {1.0f, 1.0f, 1.0f, 1.0f},
  {0.0f, 0.0f, 2.0f, 1.0f}
};

float drum_values[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
const float dist = 0.99f;
const float big_radius = 0.7f;

float objects[][5] = {
  { big_radius, dist, 0.0f, 0.0f, 1.0f },
  { dist + big_radius, 0.0f, 0.0f, 0.6f, 0.0f },
  { -dist - big_radius, 0.0f, 1.0f, 0.0f, 0.0f },
  { -big_radius, dist, 1.0f, 1.0f, 0.0f }
};

Display::~Display(){
  if (quad)
    gluDeleteQuadric(quad);
}

bool Display::initialize(int w, int h, int bpp, int flags){
  width = w; height = h;
  this->bpp = bpp;

  // initialize SDL
  window = SDL_SetVideoMode(w, h, bpp, flags);
  SDL_WM_SetCaption("OpenDrums", NULL);

  // initialize OpenGL
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

  return true;
}

void Display::render(){
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

void Display::resize(int w, int h){
  if (h == 0) h = 1;

  width = w; height = h;

  glViewport(0, 0, (GLsizei)w, (GLsizei)h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
