#include "teddyshader.hpp"

namespace Umu
{
    TeddyShader::TeddyShader(std::string vShader, std::string fShader) : Shader(vShader, fShader)
    {
        u_Translate = glGetUniformLocation(m_program, "u_Translate");
    }

    TeddyShader::~TeddyShader()
    {

    }

    //-----------------------------------------PUBLIC------------------------------------------//
    
    void TeddyShader::pushTranslationMatrix(mat4 translation)
    {
        glUniformMatrix4fv(u_Translate, 1, false, value_ptr(translation));
    }
}