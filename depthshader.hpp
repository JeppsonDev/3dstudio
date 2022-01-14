/**
 * @file depthshader.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.es)
 *
 * @brief The shader responsible for computing the depth of the scene used for shadow mapping
 *
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "shader.hpp"
#include <string>

namespace Umu
{
    class DepthShader : public Shader
    {
        public:
            /**
             * @brief Construct a new Depth Shader object
             * 
             * @param vShader 
             * @param fShader 
             */
            DepthShader(std::string vShader, std::string fShader);
    };
}