#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <assimp/cimport.h>

#include <iostream>
#include <stdint.h>
#include <vector>
#include "mesh.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "openglinput.hpp"
#include "gui.hpp"
#include "observer.hpp"

namespace Umu
{
    const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);

    struct OnCameraUpdateEvent
    {
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
    };

    class Camera
    {
        public:
            Camera();
            ~Camera();
            void update();
            glm::mat4 getViewMatrix();
            glm::mat4 getProjectionMatrix();
            Observer<OnCameraUpdateEvent> *getOnCameraUpdateObserver();
        
        private:
            glm::mat4 m_viewMatrix;
            glm::mat4 m_projectionMatrix;
            glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 4.0f);
            glm::vec3 m_oldPosition = glm::vec3(0.0f, 0.0f, 4.0f);
            glm::vec3 m_front;
            glm::vec3 m_up;
            glm::vec3 m_right;
            glm::vec3 m_referencePosition = glm::vec3(0.0f, 0.0f, 0.0f);
            bool m_updateViewMatrix = false;

            //Orientaiton
            float m_yaw = -90.0f;
            float m_pitch = 0.0f;

            //Projection
            float m_nearPlane = 1.0f;
            float m_farPlane = 500.0f;
            float m_fov = 60.0f;
            float m_top = 1.0f;
            float m_oblscale = 0.0f;
            float m_oblrad = 3.14567f/4.0f; //45 degrees

            bool m_updateProjection = false;
            bool m_updateOrtho = false;
        
            //Observers
            Observer<OnCameraUpdateEvent> *m_pOnCameraUpdateObserver;

            //Methods
            void onMouseUpdate(MouseInputEvent inputEvent);
            void onOrthographicUpdate(UpdateOrthographicEvent event);
            void onPerspectiveProjectionUpdate(UpdatePerspectiveEvent event);
    };
}