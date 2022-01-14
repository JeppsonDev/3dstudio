/**
 * @file gui.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 *
 * @brief The class for handling the GUI and rendering it
 *
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <iostream>
#include <stdint.h>
#include <vector>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "ImGuiFileDialog.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "observer.hpp"

namespace Umu
{
    /**
     * @brief Data for the perspective event
     * 
     */
    struct UpdatePerspectiveEvent
    {
        float fov=45;
        float farplane=100;
    };

    /**
     * @brief Data for the orthographic event
     * 
     */
    struct UpdateOrthographicEvent
    {
        float top=10;
        float farplane=100;
        float obliquescale=0;
        float obliqueanglerad=0;
    };

    /**
     * @brief Data for the open object event
     * 
     */
    struct OpenObjectEvent
    {
        std::string filepath="";
    };

    /**
     * @brief Data for the light event
     * 
     */
    struct OnUpdateLightEvent
    {
        float position[3] = {0.0f, 2.0f, 1.5f};
        float lightColor[3] = {1.0f, 1.0f, 1.0f};
        float ambientColor[3] = {1.0f, 1.0f, 1.0f};
    };

    /**
     * @brief Data for the update material event
     * 
     */
    struct OnUpdateMaterialEvent
    {
        float materialAmbient[3] = {0.5f, 0.5f, 0.5f};
        float materialDiffuse[3] = {0.5f, 0.5f, 0.5f};
        float materialSpecular[3] = {0.5f, 0.5f, 0.5f};
        float materialShininess = 1.0f;
        float outlineThickness = 0.0f;
    };

    /**
     * @brief Data for the texture toggle event
     * 
     */
    struct OnTextureToggle
    {
        bool textureShow = false;  
    };

    /**
     * @brief Data for the texture open event
     * 
     */
    struct OnTextureOpen
    {
        std::string filepath = "";
    };

    /**
     * @brief Data for the update shader event
     * 
     */
    struct OnUpdateShaderEvent
    {
        unsigned int type;
    };

    /**
     * @brief On select object event data
     * 
     */
    struct OnSelectObjectEvent
    {
        int objectId;
        bool flag;
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
            static Observer<OnUpdateMaterialEvent> *m_onUpdateMaterialEvent;
            static Observer<OnUpdateShaderEvent> *m_onUpdateShaderEvent;
            static Observer<OnSelectObjectEvent> *m_onSelectObjectObserver;
            static std::vector<int> m_objects;

            /**
             * @brief Renders the object file category
             * 
             */
            static void renderObjFileCategory();

            /**
             * @brief Renders the projection category
             * 
             * @param flags 
             */
            static void renderProjectionCategory(ImGuiSliderFlags flags);

            /**
             * @brief Renders the light category
             * 
             * @param flags 
             */
            static void renderLightCategory(ImGuiSliderFlags flags);

            /**
             * @brief Renders the choose shader category
             * 
             */
            static void renderChooseShaderCategory();

            /**
             * @brief Renders objects in scene category
             * 
             */
            static void renderObjectsInSceneCategory();

        public:
            /**
             * @brief Renders the gui
             * 
             */
            static void render();

            /**
             * @brief Destroys the gui
             * 
             */
            static void destroy();

            /**
             * @brief Adds an object to the list
             * 
             */
            static void addObject(int objectId);

            /**
             * @brief Get the Update Perspective Observer object
             * 
             * @return Observer<UpdatePerspectiveEvent>* 
             */
            static Observer<UpdatePerspectiveEvent> *getUpdatePerspectiveObserver();

            /**
             * @brief Get the Update Orthographic Observer object
             * 
             * @return Observer<UpdateOrthographicEvent>* 
             */
            static Observer<UpdateOrthographicEvent> *getUpdateOrthographicObserver();

            /**
             * @brief Get the Open Object Observer object
             * 
             * @return Observer<OpenObjectEvent>* 
             */
            static Observer<OpenObjectEvent> *getOpenObjectObserver();

            /**
             * @brief Get the On Update Light Observer object
             * 
             * @return Observer<OnUpdateLightEvent>* 
             */
            static Observer<OnUpdateLightEvent> *getOnUpdateLightObserver();

            /**
             * @brief Get the On Texture Toggle object
             * 
             * @return Observer<OnTextureToggle>* 
             */
            static Observer<OnTextureToggle> *getOnTextureToggle();

            /**
             * @brief Get the On Texture Open object
             * 
             * @return Observer<OnTextureOpen>* 
             */
            static Observer<OnTextureOpen> *getOnTextureOpen();

            /**
             * @brief Get the On Update Material Observer object
             * 
             * @return Observer<OnUpdateMaterialEvent>* 
             */
            static Observer<OnUpdateMaterialEvent> *getOnUpdateMaterialObserver();

            /**
             * @brief Get the On Update Shader Event object
             * 
             * @return Observer<OnUpdateShaderEvent>* 
             */
            static Observer<OnUpdateShaderEvent> *getOnUpdateShaderEvent();

            /**
             * @brief Gets On Select Object Event
             * 
             * @return Observer<OnSelectObjectEvent>* 
             */
            static Observer<OnSelectObjectEvent> *getOnSelectObjectObserver();
    };
}