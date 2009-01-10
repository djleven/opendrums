# The MIT License
# 
# Copyright (c) 2008 Rob Britton
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

CC     = g++
LIBS   = sdl 
CFLAGS = `pkg-config --cflags $(LIBS)` -ansi -pedantic -Werror -Wall
LFLAGS = `pkg-config --libs $(LIBS)` -lSDL_mixer -lGL -lGLU
EXE    = out
OBJS   = main.o display.o sound.o

$(EXE): $(OBJS)
	$(CC) $(LFLAGS) -o $(EXE) $(OBJS)

main.o: drums.cpp drums.cpp
	$(CC) -c -o main.o drums.cpp $(CFLAGS)

display.o: display.cpp display.h
	$(CC) -c -o display.o display.cpp $(CFLAGS)

sound.o: sound.cpp sound.h
	$(CC) -c -o sound.o sound.cpp $(CFLAGS)

clean:
	rm -rf $(OBJS) $(EXE)
