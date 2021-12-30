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
#include "camera.hpp"

#include "imgui.h"
#include "ImGuiFileDialog.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "gui.hpp"
#include "scene.hpp"

namespace Umu
{
    class OpenGLWindow
    {
        public:
            OpenGLWindow(std::string title, int width, int height);
            ~OpenGLWindow(void);

            void start(Scene *scene, Render3D *renderer);
            void DrawGui();
        private:
            GLFWwindow *glfwWindow;
            static void onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods);
            static void onWindowResize(GLFWwindow *window, int width, int height);
    };
}