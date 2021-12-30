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

        // Create Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Set Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
        ImGui_ImplOpenGL3_Init(NULL);

        glPointSize(5.0);
        glLineWidth(1.0);
        glClearColor(0.0, 0.0, 0.0, 0.0);

        glViewport(0, 0, width, height);
    }

    OpenGLWindow::~OpenGLWindow(void)
    {
        // Cleanup ImGui
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    //-----------------------------------------PUBLIC------------------------------------------//

    void OpenGLWindow::DrawGui()
    {
        Gui::render();
    }

    void OpenGLWindow::start(Scene *scene, Render3D *renderer)
    {
        glfwSetKeyCallback(glfwWindow, OpenGLInput::onKeyEvent);
        glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPosCallback(glfwWindow, OpenGLInput::onMouseEvent);

        while(!glfwWindowShouldClose(glfwWindow))
        {
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            DrawGui();

            renderer->render();
            scene->render(renderer);

            //Render imgui
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            if(OpenGLInput::isKeyPressed("shift"))
            {
                glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
            else if(OpenGLInput::isKeyReleased("shift"))
            {
                glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }

            glfwSetFramebufferSizeCallback(glfwWindow , onWindowResize);

            glfwSwapBuffers(glfwWindow);
            glfwPollEvents();
        }
    }

    void OpenGLWindow::onWindowResize(GLFWwindow* window, int width, int height)
    {
        if(glfwGetCurrentContext() == nullptr)
            return;

        glViewport(0.0, 0.0, width, height);
    }

    //-----------------------------------------PRIVATE------------------------------------------//
}