#pragma once

#include "shader.hpp"

namespace Umu 
{
    class TeddyShader : public Shader
    {
        public:
            TeddyShader(std::string vShader, std::string fShader);
            ~TeddyShader(void);
            
            void pushTranslationMatrix(mat4 translation);
        private:
            GLuint u_Translate;
    };
}