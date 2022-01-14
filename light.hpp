/**
 * @file light.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 *
 * @brief The class representing the Light object in world
 *
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "gui.hpp"

namespace Umu
{
    class Light
    {
        public:
            /**
             * @brief Construct a new Light object
             * 
             */
            Light();
            
            /**
             * @brief Sets Position
             * 
             * @param position 
             */
            void setPosition(glm::vec3 position);

            /**
             * @brief Sets Ambient Light
             * 
             * @param ambientLight 
             */
            void setAmbientLight(glm::vec3 ambientLight);

            /**
             * @brief Sets Light Intensity
             * 
             * @param lightIntensity 
             */
            void setLightIntensity(glm::vec3 lightIntensity);

            /**
             * @brief Gets Position
             * 
             * @return glm::vec3 
             */
            glm::vec3 getPosition();

            /**
             * @brief Gets Ambient Light
             * 
             * @return glm::vec3 
             */
            glm::vec3 getAmbientLight();

            /**
             * @brief Gets Light Intensity
             * 
             * @return glm::vec3 
             */
            glm::vec3 getLightIntensity();
        private:
            glm::vec3 m_lightPosition;
            glm::vec3 m_ambientLight;
            glm::vec3 m_lightIntensity;
    };
}