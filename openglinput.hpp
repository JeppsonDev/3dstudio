/**
 * @file openglinput.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 *
 * @brief The class representing the input from opengl 
 *
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "observer.hpp"

namespace Umu
{
    /**
     * @brief Data for the mouse input event
     * 
     */
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
            /**
             * @brief When a key is pressed
             * 
             * @param window 
             * @param key 
             * @param scancode 
             * @param action 
             * @param mods 
             */
            static void onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods);

            /**
             * @brief When the mouse moves
             * 
             * @param window 
             * @param xpos 
             * @param ypos 
             */
            static void onMouseEvent(GLFWwindow *window, double xpos, double ypos);

            /**
             * @brief Checks if a key is pressed
             * 
             * @param key 
             * @return true 
             * @return false 
             */
            static bool isKeyPressed(std::string key);

            /**
             * @brief Checks if a key is released
             * 
             * @param key 
             * @return true 
             * @return false 
             */
            static bool isKeyReleased(std::string key);

            /**
             * @brief Gets Mouse Input Observer
             * 
             * @return Observer<MouseInputEvent>* 
             */
            static Observer<MouseInputEvent> *getMouseInputObserver();
        private:
            static std::unordered_map<std::string, int> inputMap;
            static Observer<MouseInputEvent> *m_mouseInputObserver;
    };
}