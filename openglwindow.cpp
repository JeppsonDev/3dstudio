#include "openglwindow.hpp"

namespace Umu
{
    OpenGLWindow::OpenGLWindow(std::string title, int width, int height)
    {
        if (!glfwInit())
            //TODO: Print an error here
            return;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        if (glfwWindow == nullptr) 
        {
            glfwTerminate();
            std::cerr << "Could not open window or initialize OpenGL context." << std::endl;
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(glfwWindow);
        glfwSwapInterval(1); 

        glewExperimental = GL_TRUE;
        GLenum glewError = glewInit();
        if(glewError != GLEW_OK)
        {
            std::cout << "glew init error:" << std::endl << glewGetErrorString(glewError) << std::endl;
            exit(EXIT_FAILURE);
        }

        if (!GLEW_VERSION_4_3) 
        {
            std::cout << "Warning: OpenGL 4.3+ not supported by the GPU!" << std::endl;
            std::cout << "Decreace supported OpenGL version if needed." << std::endl;
        }

        glPointSize(5.0);
        glLineWidth(1.0);
        glClearColor(0.0, 0.0, 0.0, 0.0);

        glViewport(0, 0, width, height);
    }

    OpenGLWindow::~OpenGLWindow(void)
    {

    }

    void OpenGLWindow::start(AssimpLoader *loader, Render3D *renderer)
    {
        renderer->prepare(loader->getVertices(), loader->getIndicies());

        glfwSetKeyCallback(glfwWindow, OpenGLInput::onKeyEvent);

        while(!glfwWindowShouldClose(glfwWindow))
        {
            renderer->render();
            glfwSwapBuffers(glfwWindow);
            glfwWaitEvents();
        }
    }
}