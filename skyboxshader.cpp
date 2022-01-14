#include "skyboxshader.hpp"

namespace Umu
{
    SkyboxShader::SkyboxShader(std::string vShader, std::string fShader) : Shader()
    {
        m_program = initProgram(vShader, fShader);

        m_properties["vPosition"] = glGetAttribLocation(m_program, "vPosition");
        m_properties["u_View"] = glGetUniformLocation(m_program, "u_View");
        m_properties["u_Projection"] = glGetUniformLocation(m_program, "u_Projection");
        m_properties["u_Skybox"] = glGetUniformLocation(m_program, "u_Skybox");
    }
}