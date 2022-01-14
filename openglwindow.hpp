/**
 * @file openglwindow.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 * 
 * @brief The class representing a GLFW window
 *
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
#include <vector>
#include <stdint.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "ImGuiFileDialog.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "gui.hpp"
#include "scene.hpp"
#include "render3d.hpp"
#include "assimp.hpp"
#include "openglinput.hpp"
#include "camera.hpp"

namespace Umu
{
    class OpenGLWindow
    {
        public:
            /**
             * @brief Construct a new Open G L Window object
             * 
             * @param title 
             * @param width 
             * @param height 
             */
            OpenGLWindow(std::string title, int width, int height);

            /**
             * @brief Destroy the Open G L Window object
             * 
             */
            ~OpenGLWindow(void);

            /**
             * @brief Starts the window
             * 
             * @param scene 
             * @param renderer 
             */
            void start(Scene *scene, Render3D *renderer);

        private:
            GLFWwindow *glfwWindow;

            /**
             * @brief When the window is resized
             * 
             * @param window 
             * @param width 
             * @param height 
             */
            static void onWindowResize(GLFWwindow *window, int width, int height);
    };
}