#include "light.hpp"

namespace Umu
{
    Light::Light()
    {
    }

    //-----------------------------------------PUBLIC------------------------------------------//
    void Light::setAmbientLight(glm::vec3 ambientLight)
    {
        m_ambientLight = ambientLight;
    }

    void Light::setLightIntensity(glm::vec3 lightIntensity)
    {
        m_lightIntensity = lightIntensity;
    }

    void Light::setPosition(glm::vec3 position)
    {
        m_lightPosition = position;
    }
    
    glm::vec3 Light::getPosition()
    {
        return m_lightPosition;
    }

    glm::vec3 Light::getLightIntensity()
    {
        return m_lightIntensity;
    }

    glm::vec3 Light::getAmbientLight()
    {
        return m_ambientLight;
    }

   //-----------------------------------------PRIVATE------------------------------------------//
}