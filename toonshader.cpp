#include "toonshader.hpp"

namespace Umu
{
    ToonShader::ToonShader(std::string vShader, std::string fShader) : Shader()
    {
        m_program = initProgram(vShader, fShader);
        
        m_properties["vPosition"] = glGetAttribLocation(m_program, "vPosition");
        m_properties["vNormal"] = glGetAttribLocation(m_program, "vNormal");
        m_properties["vTexCoords"] = glGetAttribLocation(m_program, "vTexCoords");
        m_properties["u_Model"] = glGetUniformLocation(m_program, "u_Model");
        m_properties["u_View"] = glGetUniformLocation(m_program, "u_View");
        m_properties["u_Projection"] = glGetUniformLocation(m_program, "u_Projection");
        m_properties["u_LightSpaceMatrix"] = glGetUniformLocation(m_program, "u_LightSpaceMatrix");

        m_properties["u_CameraPosition"] = glGetUniformLocation(m_program, "u_CameraPosition");
        m_properties["u_LightPosition"] = glGetUniformLocation(m_program, "u_LightPosition");
        m_properties["u_AmbientLight"] = glGetUniformLocation(m_program, "u_AmbientLight");
        m_properties["u_LightIntensity"] = glGetUniformLocation(m_program, "u_LightIntensity");
        m_properties["u_AmbientConstant"] = glGetUniformLocation(m_program, "u_AmbientConstant");
        m_properties["u_DiffuseConstant"] = glGetUniformLocation(m_program, "u_DiffuseConstant");
        m_properties["u_SpecularConstant"] = glGetUniformLocation(m_program, "u_SpecularConstant");
        m_properties["u_Shininess"] = glGetUniformLocation(m_program, "u_Shininess");
        m_properties["u_Texture"] = glGetUniformLocation(m_program, "u_Texture");
        m_properties["u_DepthTexture"] = glGetUniformLocation(m_program, "u_DepthTexture");
        m_properties["u_ShouldRenderTexture"] = glGetUniformLocation(m_program, "u_ShouldRenderTexture");
        m_properties["u_OutlineThickness"] = glGetUniformLocation(m_program, "u_OutlineThickness");
    }
}