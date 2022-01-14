/**
 * @file scene.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 *
 * @brief The class representing a 3D scene. By default the scene loads shadow mapping and a skybox
 *
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */
 
#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/constants.hpp>

#include "assimp.hpp"
#include "camera.hpp"
#include "render3d.hpp"
#include "light.hpp"
#include "skybox.hpp"
#include "global.hpp"
#include "depthshader.hpp"
#include "shadowmap.hpp"
#include "actor.hpp"
#include "texture2d.hpp"
#include "skyboxshader.hpp"
#include "toonshader.hpp"

namespace Umu
{
    class Scene
    {
        public: 
            /**
             * @brief Construct a new Scene object
             * 
             */
            Scene();
            
            /**
             * @brief Destroy the Scene object
             * 
             */
            ~Scene();

            /**
             * @brief Renders the scene
             * 
             * @param renderer 
             */
            void render(Render3D *renderer);

            /**
             * @brief Adds an object to the scene
             * 
             * @param obj 
             */
            void addObject(Object *obj);

            /**
             * @brief On the window update event
             * 
             * @param event 
             */
            void onUpdateWindow(OnUpdateWindowEvent event);

        private:
            Shader* m_pShaders[3];
            Shader *m_pMainShader;
            Shader *m_pSkyboxShader;
            Shader *m_pDepthShader;
            Shader *m_pOutlineShader;
            Camera *m_pCamera;
            Light *m_pLight;
            Skybox *m_pSkybox;
            ShadowMap *m_pShadowMap;
            std::vector<Object*> m_objects;

            /**
             * @brief Updates the scene
             * 
             */
            void update();

            /**
             * @brief Renders the shadow map
             * 
             * @param renderer 
             */
            void renderShadowMap(Render3D *renderer);

            /**
             * @brief Renders the scene
             * 
             * @param renderer 
             * @param shader 
             */
            void renderScene(Render3D *renderer, Shader *shader, bool onlyRenderEnabledObjects=false);

            /**
             * @brief Handles when a file tries to be opened
             * 
             */
            void handleFileOpen();

            /**
             * @brief Event for when an object should load from file
             * 
             * @param event 
             */
            void onObjectOpen(OpenObjectEvent event);

            /**
             * @brief Event for when the camera updates
             * 
             * @param event 
             */
            void onCameraUpdate(OnCameraUpdateEvent event);

            /**
             * @brief Event for when light values from GUI updates
             * 
             * @param event 
             */
            void onLightUpdate(OnUpdateLightEvent event);

            /**
             * @brief Event for when GUI updates the shaders
             * 
             * @param event 
             */
            void onShaderUpdate(OnUpdateShaderEvent event);

            /**
             * @brief On select object event
             * 
             * @param event 
             */
            void onSelectObjectEvent(OnSelectObjectEvent event);
    };
}