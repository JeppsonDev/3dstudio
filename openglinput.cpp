
#include "openglinput.hpp"

namespace Umu
{
    std::unordered_map<std::string, int> OpenGLInput::inputMap;

    void OpenGLInput::onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if(key == GLFW_KEY_UP)
        {
            if(action == GLFW_PRESS)
            {
                inputMap["up"] = true;
            }
            else if(action == GLFW_RELEASE)
            {
                inputMap["up"] = false;
            }
        }

        if(key == GLFW_KEY_DOWN)
        {
            if(action == GLFW_PRESS)
            {
                inputMap["down"] = true;
            }
            else if(action == GLFW_RELEASE)
            {
                inputMap["down"] = false;
            }
        }

        if(key == GLFW_KEY_LEFT)
        {
            if(action == GLFW_PRESS)
            {
                inputMap["left"] = true;
            }
            else if(action == GLFW_RELEASE)
            {
                inputMap["left"] = false;
            }
        }

        if(key == GLFW_KEY_RIGHT)
        {
            if(action == GLFW_PRESS)
            {
                inputMap["right"] = true;
            }
            else if(action == GLFW_RELEASE)
            {
                inputMap["right"] = false;
            }
        }

        if(key == GLFW_KEY_T)
        {
            if(action == GLFW_PRESS)
            {
                inputMap["t"] = true;
            }
            else if(action == GLFW_RELEASE)
            {
                inputMap["t"] = false;
            }
        }

        if(key == GLFW_KEY_R)
        {
            if(action == GLFW_PRESS)
            {
                inputMap["r"] = true;
            }
            else if(action == GLFW_RELEASE)
            {
                inputMap["r"] = false;
            } 
        }
    }

    bool OpenGLInput::isKeyPressed(std::string key)
    {
        return inputMap[key];
    }

    bool OpenGLInput::isKeyReleased(std::string key)
    {
        return !inputMap[key];
    }
}