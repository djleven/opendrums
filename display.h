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

