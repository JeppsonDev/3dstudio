/**
 * @file skybox.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 *
 * @brief The skybox class handles the rendering and construction of the world skybox
 *
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include <string>
#include <vector>

#include "camera.hpp"
#include "shader.hpp"

namespace Umu
{
    class Skybox
    {
        public:
            /**
             * @brief Construct a new Skybox object
             * 
             */
            Skybox();

            /**
             * @brief Destroy the Skybox object
             * 
             */
            ~Skybox();

            /**
             * @brief Renders the skybox
             * 
             * @param camera 
             * @param shader 
             */
            void render(Camera* camera, Shader *shader);            
        private:
            unsigned int m_CubemapTexture;
            unsigned int m_SkyboxVAO;
            unsigned int m_SkyboxVBO;

            /**
             * @brief Prepares the skybox
             * 
             */
            void prepare();

            /**
             * @brief Loads the texture
             * 
             * @param faces 
             * @return unsigned int 
             */
            unsigned int loadTexture(std::vector<std::string> faces);
    };
}