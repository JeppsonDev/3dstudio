#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "assimp.hpp"
#include "openglwindow.hpp"
#include "render3d.hpp"

int main(void) 
{
    Umu::AssimpLoader *loader = new Umu::AssimpLoader();

    if(loader->load("teddy.obj")) 
    {
        std::cout << "Success" << std::endl;
    }

    loader->print();

    Umu::OpenGLWindow *window = new Umu::OpenGLWindow("Title", 1920/2, 1080/2);
    Umu::Render3D *renderer = new Umu::Render3D();

    window->start(loader, renderer);

    delete loader;
    delete window;
    delete renderer;

    return 0;
}