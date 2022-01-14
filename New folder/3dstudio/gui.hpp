#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <assimp/cimport.h>

#include <iostream>
#include <stdint.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "imgui.h"
#include "ImGuiFileDialog.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "observer.hpp"

namespace Umu
{
    struct UpdatePerspectiveEvent
    {
        float fov=45;
        float farplane=100;
    };

    struct UpdateOrthographicEvent
    {
        float top=10;
        float farplane=100;
        float obliquescale=0;
        float obliqueanglerad=0;
    };

    struct OpenObjectEvent
    {
        std::string filepath="";
    };

    struct OnUpdateLightEvent
    {
        float position[3] = {-10.0f, 4.0f, 1.0f};
        float lightColor[3] = {1.0f, 1.0f, 1.0f};
        float ambientColor[3] = {0.2f, 0.2f, 0.2f};

        float materialAmbient[3] = {.5f, .5f, .5f};
        float materialDiffuse[3] = {.5f, .5f, .5f};
        float materialSpecular[3] = {.5f, .5f, .5f};
        float materialShininess = 1.0f;
    };

    struct OnTextureToggle
    {
        bool textureShow = false;  
    };

    struct OnTextureOpen
    {
        std::string filepath = "";
    };

    class Gui
    {
        private:
            static Observer<UpdatePerspectiveEvent> *m_updatePerspectiveObserver;
            static Observer<UpdateOrthographicEvent> *m_updateOrthographicObserver;
            static Observer<OpenObjectEvent> *m_openObjectObserver;
            static Observer<OnUpdateLightEvent> *m_onUpdateLightObserver;
            static Observer<OnTextureToggle> *m_onTextureToggle;
            static Observer<OnTextureOpen> *m_onTextureOpen;

            static void renderObjFileCategory();
            static void renderProjectionCategory(ImGuiSliderFlags flags);
            static void renderLightCategory(ImGuiSliderFlags flags);
        public:
            static void render();

            static Observer<UpdatePerspectiveEvent> *getUpdatePerspectiveObserver();
            static Observer<UpdateOrthographicEvent> *getUpdateOrthographicObserver();
            static Observer<OpenObjectEvent> *getOpenObjectObserver();
            static Observer<OnUpdateLightEvent> *getOnUpdateLightObserver();
            static Observer<OnTextureToggle> *getOnTextureToggle();
            static Observer<OnTextureOpen> *getOnTextureOpen();
    };
}