/**
 * @file shadowmap.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 *
 * @brief Class representing a shadow map. Handles all the data and generates the textures
 *
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Umu
{
    class ShadowMap
    {
        public:
            /**
             * @brief Construct a new Shadow Map object
             * 
             */
            ShadowMap();

            /**
             * @brief Calculates the light space matrix, view and projection for the shadow map
             * 
             * @param lightPosition 
             * @return glm::mat4 
             */
            glm::mat4 calculateLightSpace(glm::vec3 lightPosition);
            
            /**
             * @brief Prepares the shadow map
             * 
             */
            void prepare();

            /**
             * @brief Returns to normal rendering
             * 
             */
            void unprepare();

            /**
             * @brief Binds the shadow map texture (depth texture)
             * 
             * @param i 
             */
            void bind(int i);

            /**
             * @brief Unbinds 
             * 
             */
            void unbind();

        private:
            unsigned int m_fbo;
            unsigned int m_depthMapTextureId;

            /**
             * @brief Initilizes the shadowmap
             * 
             */
            void init();
    };
}