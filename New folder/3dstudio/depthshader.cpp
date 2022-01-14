#include "depthshader.hpp"

namespace Umu
{
    DepthShader::DepthShader(std::string vshader, std::string fshader) : Shader()
    {
        m_program = initProgram(vshader, fshader);

        m_properties["vPosition"] = glGetAttribLocation(m_program, "vPosition");
        m_properties["u_Model"] = glGetUniformLocation(m_program, "u_Model");
        m_properties["u_LightSpaceMatrix"] = glGetUniformLocation(m_program, "u_LightSpaceMatrix");
    }
}