/**
 * @file camera.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 *
 * @brief The class responsible for handling the first person camera in the scene
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

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mesh.hpp"
#include "gui.hpp"
#include "observer.hpp"
#include "openglinput.hpp"

namespace Umu
{
    //consts
    const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
    const int PERSPECTIVE = 0;
    const int ORTHOGRAPHIC = 1;

    /**
     * @brief Camera update event
     * 
     */
    struct OnCameraUpdateEvent
    {
        glm::vec3 position;
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
    };

    class Camera
    {
        public:
            /**
             * @brief Construct a new Camera object
             * 
             */
            Camera();

            /**
             * @brief Destroy the Camera object
             * 
             */
            ~Camera();

            /**
             * @brief Update the Camera object
             * 
             */
            void update();

            /**
             * @brief Get the View Matrix object
             * 
             * @return glm::mat4 
             */
            glm::mat4 getViewMatrix();

            /**
             * @brief Get the Projection Matrix object
             * 
             * @return glm::mat4 
             */
            glm::mat4 getProjectionMatrix();

            /**
             * @brief Get the On Camera Update Observer object
             * 
             * @return Observer<OnCameraUpdateEvent>* 
             */
            Observer<OnCameraUpdateEvent> *getOnCameraUpdateObserver();

            /**
             * @brief Use the perspective projection
             * 
             */
            void usePerspectiveProjection();

            /**
             * @brief Use orthographic projection
             * 
             */
            void useOrthographicProjection();

            /**
             * @brief Update the projection
             * 
             */
            void updateProjection();

            /**
             * @brief Get the position
             * 
             * @return glm::vec3 
             */
            glm::vec3 getPosition();
        
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
            float m_farPlane = 500.0f;
            float m_fov = 60.0f;
            float m_top = 1.0f;
            float m_oblscale = 0.0f;
            float m_oblrad = 3.14567f/4.0f; //45 degrees
            int m_projectionType = PERSPECTIVE;

            bool m_updateProjection = false;
            bool m_updateOrtho = false;
        
            //Observers
            Observer<OnCameraUpdateEvent> *m_pOnCameraUpdateObserver;

            /**
             * @brief On mouse update event
             * 
             * @param inputEvent 
             */
            void onMouseUpdate(MouseInputEvent inputEvent);

            /**
             * @brief Update the orthographic projection event
             * 
             * @param event 
             */
            void onOrthographicUpdate(UpdateOrthographicEvent event);

            /**
             * @brief Update the perspective projection event
             * 
             * @param event 
             */
            void onPerspectiveProjectionUpdate(UpdatePerspectiveEvent event);

            /**
             * @brief Update the shader event
             * 
             * @param event 
             */
            void onShaderUpdate(OnUpdateShaderEvent event);
    };
}