#pragma once

#include <string>
#include "shader.hpp"

namespace Umu
{
    class DepthShader : public Shader
    {
        public:
            DepthShader(std::string vShader, std::string fShader);
    };
}