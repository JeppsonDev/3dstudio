
#include "openglinput.hpp"

namespace Umu
{
    //Static variables
    std::unordered_map<std::string, int> OpenGLInput::inputMap;
    Observer<MouseInputEvent> *OpenGLInput::m_mouseInputObserver = new Observer<MouseInputEvent>();

    // Local variables to file
    static float xMousePos;
    static float yMousePos;
    static float lastMouseX;
    static float lastMouseY;

    //-----------------------------------------PUBLIC------------------------------------------//
    void OpenGLInput::onMouseEvent(GLFWwindow *window, double xpos, double ypos)
    {
        MouseInputEvent mouseInputEvent;

        lastMouseX = xMousePos;
        lastMouseY = yMousePos;

        xMousePos = mouseInputEvent.xMouse = xpos;
        yMousePos = mouseInputEvent.yMouse = ypos;

        mouseInputEvent.xMouseDelta = lastMouseX - mouseInputEvent.xMouse;
        mouseInputEvent.yMouseDelta = lastMouseY - mouseInputEvent.yMouse;

        OpenGLInput::getMouseInputObserver()->invokeEvents(mouseInputEvent);
    }

    void OpenGLInput::onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if(key == GLFW_KEY_LEFT_SHIFT)
        {
            if(action == GLFW_PRESS)
            {
                inputMap["shift"] = true;
            }
            else if(action == GLFW_RELEASE)
            {             
                inputMap["shift"] = false;
            }
        }

        if(key == GLFW_KEY_W)
        {
            if(action == GLFW_PRESS)
            {
                inputMap["w"] = true;
            }
            else if(action == GLFW_RELEASE)
            {
                inputMap["w"] = false;
            }
        }

        if(key == GLFW_KEY_A)
        {
            if(action == GLFW_PRESS)
            {
                inputMap["a"] = true;
            }
            else if(action == GLFW_RELEASE)
            {
                inputMap["a"] = false;
            }
        }

        if(key == GLFW_KEY_D)
        {
            if(action == GLFW_PRESS)
            {
                inputMap["d"] = true;
            }
            else if(action == GLFW_RELEASE)
            {
                inputMap["d"] = false;
            }
        }

        if(key == GLFW_KEY_Q)
        {
            if(action == GLFW_PRESS)
            {
                inputMap["q"] = true;
            }
            else if(action == GLFW_RELEASE)
            {
                inputMap["q"] = false;
            }
        }

        if(key == GLFW_KEY_E)
        {
            if(action == GLFW_PRESS)
            {
                inputMap["e"] = true;
            }
            else if(action == GLFW_RELEASE)
            {
                inputMap["e"] = false;
            }
        }

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

        if(key == GLFW_KEY_S)
        {
            if(action == GLFW_PRESS)
            {
                inputMap["s"] = true;
            }
            else if(action == GLFW_RELEASE)
            {
                inputMap["s"] = false;
            }
        }

        if(key == GLFW_KEY_O)
        {
            if(action == GLFW_PRESS)
            {
                inputMap["o"] = true;
            }
            else if(action == GLFW_RELEASE)
            {
                inputMap["o"] = false;
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

    Observer<MouseInputEvent> *OpenGLInput::getMouseInputObserver()
    {
        return m_mouseInputObserver;
    }

    //-----------------------------------------PRIVATE------------------------------------------//
}