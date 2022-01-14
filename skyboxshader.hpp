/**
 * @file skyboxshader.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 *
 * @brief The construciton of the shader for the skybox
 *
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "shader.hpp"

namespace Umu
{
    class SkyboxShader : public Shader
    {
        public:
            /**
             * @brief Construct a new Skybox Shader object
             * 
             * @param vShader 
             * @param fShader 
             */
            SkyboxShader(std::string vShader, std::string fShader);
    };
}