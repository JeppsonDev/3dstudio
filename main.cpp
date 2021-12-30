#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "openglwindow.hpp"
#include "render3d.hpp"
#include "scene.hpp"
#include "openglinput.hpp"

int main(void) 
{
    //Inititilize the engine
    Umu::OpenGLWindow *window = new Umu::OpenGLWindow("Title", 960, 540);
    Umu::Render3D *renderer = new Umu::Render3D();

    //Initilize the scene
    Umu::Scene *scene = new Umu::Scene();

    window->start(scene, renderer);

    delete scene;
    delete window;
    delete renderer;

    return 0;
}