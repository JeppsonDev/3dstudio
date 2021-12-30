#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/constants.hpp>
#include "assimp.hpp"
#include "camera.hpp"
#include "render3d.hpp"
#include "object.hpp"
#include "light.hpp"

namespace Umu
{
    class Scene
    {
        public: 
            Scene();
            ~Scene();
            void render(Render3D *renderer);
            void addObject(Object *obj);

        private:
            Shader *m_pMainShader;
            Camera *m_pCamera;
            Light *m_pLight;
            std::vector<Object*> m_objects;

            void handleFileOpen();
            void onObjectOpen(OpenObjectEvent event);
            void onCameraUpdate(OnCameraUpdateEvent event);
            void onLightUpdate(OnUpdateLightEvent event);
    };
}