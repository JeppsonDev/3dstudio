#
#  Linux and MS Windows Makefile for Workshop 1
#  Computer Graphics course
#  Dept Computing Science, Umea University
#  Stefan Johansson, stefanj@cs.umu.se
#  Modified by Filip Henningsson, floop@cs.umu.se
#
SRC = ./
TARGET = main

OBJS = $(SRC)/main.o $(SRC)/assimp.o $(SRC)/openglwindow.o $(SRC)/render3d.o $(SRC)/shader.o $(SRC)/mesh.o $(SRC)/teddyshader.o $(SRC)/openglinput.o

CXX = g++

DBFLAGS = -O0 -g3 -ggdb3 -fno-inline
#DBFLAGS = -O2
WFLAGS  = -Wall -std=c++11

# Uncomment if you have local libraries or headers in subfolders lib and include
IFLAGS = #-Iinclude
LFLAGS = #-Llib 

ifeq ($(OS), Windows_NT)
# -DWINDOWS_BUILD needed to deal with Windows use 0f \ instead of / in path
# Unless it's completely unnecessary and handled by the compiler.
DEFS      = -DWINDOWS_BUILD
GLFLAGS   = -DGLEW_STATIC
OSLDFLAGS = -static -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32
else
DEFS    = -DIMGUI_IMPL_OPENGL_LOADER_GL3W
GLFLAGS = `pkg-config --cflags glfw3` 
# gl3w seemingly needs libdl
LGLFLAGS = `pkg-config --libs glfw3` -lm -ldl -lGL -lGLEW -lglfw3 -lassimp
ELDFLAGS = -export-dynamic -lXext -lX11 
endif

CXXFLAGS = $(WFLAGS) $(DFLAGS) $(GLFLAGS)

CXXFLAGS = $(DBFLAGS) $(DEFS) $(WFLAGS) $(IFLAGS) $(DFLAGS) $(GLFLAGS)
LDFLAGS  = $(ELDFLAGS) $(LGLFLAGS) $(OSLDFLAGS)


all: $(TARGET)
clean:
ifeq ($(OS), Windows_NT)
	del /Q /S *.o
else
	rm -f $(OBJS) $(TARGET)
endif

.SUFFIXES: .o .c .cpp .cxx .cc
.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"
.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"
.cc.o:
	$(CXX) -c $(CXXFLAGS) $<
.c.o:
	$(CXX) -c $(CXXFLAGS) $<
$(TARGET): $(OBJS)
	$(CXX) $(LFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS) 
