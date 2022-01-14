/**
 * @file toonshader.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 *
 * @brief The class for the toonshader
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
    class ToonShader : public Shader
    {
        public:
            /**
             * @brief Construct a new Toon Shader object
             * 
             * @param vShader 
             * @param fShader 
             */
            ToonShader(std::string vShader, std::string fShader);
    };
}