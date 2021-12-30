#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <vector>
#include "observer.hpp"

namespace Umu
{
    struct MouseInputEvent
    {
        float xMouse;
        float yMouse;
        float xMouseDelta;
        float yMouseDelta;
    };

    class OpenGLInput
    {
        public: 
            static void onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods);
            static void onMouseEvent(GLFWwindow *window, double xpos, double ypos);
            static bool isKeyPressed(std::string key);
            static bool isKeyReleased(std::string key);
            static Observer<MouseInputEvent> *getMouseInputObserver();
        private:
            static std::unordered_map<std::string, int> inputMap;
            static Observer<MouseInputEvent> *m_mouseInputObserver;
    };
}