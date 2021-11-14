#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_map>

namespace Umu
{
    class OpenGLInput
    {
        public:
            static void onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods);
            static bool isKeyPressed(std::string);
            static bool isKeyReleased(std::string);
        private:
            static std::unordered_map<std::string, int> inputMap;
    };
}