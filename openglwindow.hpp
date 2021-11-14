#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
#include <vector>
#include <stdint.h>
#include "render3d.hpp"
#include "assimp.hpp"
#include "openglinput.hpp"

namespace Umu
{
    class OpenGLWindow
    {
        public:
            OpenGLWindow(std::string title, int width, int height);
            ~OpenGLWindow(void);

            void start(AssimpLoader *loader, Render3D *renderer);
        private:
            GLFWwindow *glfwWindow;

        private:
            static void onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods);
    };
}