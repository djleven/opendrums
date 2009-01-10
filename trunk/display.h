#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Display{
  int width, height, bpp, flags;
  SDL_Surface * window;
  GLUquadricObj * quad;
public:
  Display() : width(0), height(0), bpp(0), flags(0), window(NULL), quad(NULL) {}
  ~Display();

  bool initialize(int w, int h, int bpp, int flags = 0);
  void render();
  void resize(int w, int h);
};

#endif

