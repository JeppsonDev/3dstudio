#
#  Linux and MS Windows Makefile for Workshop 1
#  Computer Graphics course
#  Dept Computing Science, Umea University
#  Stefan Johansson, stefanj@cs.umu.se
#  Modified by Filip Henningsson, floop@cs.umu.se
#
SRC = ./
OUT = $(SRC)
IMGUI_DIR = ./ImGui
TARGET = $(OUT)/main

OBJS = $(OUT)/depthshader.o $(OUT)/actor.o $(OUT)/texture2d.o $(OUT)/light.o $(OUT)/transform.o $(OUT)/object.o $(OUT)/scene.o $(OUT)/model.o $(OUT)/main.o $(OUT)/assimp.o $(OUT)/openglwindow.o $(OUT)/render3d.o $(OUT)/shader.o $(OUT)/mesh.o $(OUT)/openglinput.o  $(OUT)/camera.o $(OUT)/gui.o \
	$(IMGUI_DIR)/imgui.o \
	$(IMGUI_DIR)/imgui_demo.o \
	$(IMGUI_DIR)/imgui_draw.o \
	$(IMGUI_DIR)/imgui_tables.o \
	$(IMGUI_DIR)/imgui_widgets.o \
	$(IMGUI_DIR)/imgui_impl_glfw.o \
	$(IMGUI_DIR)/imgui_impl_opengl3.o \
	$(IMGUI_DIR)/ImGuiFileDialog/ImGuiFileDialog.o

CXX = g++

DBFLAGS = -O0 -g3 -ggdb3 -fno-inline
#DBFLAGS = -O2
WFLAGS  = -Wall -std=c++2a

# Uncomment if you have local libraries or headers in subfolders lib and include
IFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/ImGuiFileDialog
LFLAGS = #-Llib

IMGUIFLAGS = -DIMGUI_IMPL_OPENGL_LOADER_GLEW

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

CXXFLAGS = $(DBFLAGS) $(DEFS) $(WFLAGS) $(IFLAGS) $(DFLAGS) $(GLFLAGS) $(IMGUIFLAGS)
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
