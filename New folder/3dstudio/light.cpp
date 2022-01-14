#include "light.hpp"

namespace Umu
{
    Light::Light(glm::vec3 position)
    {
        m_lightPosition = position;
    }

    void Light::setPosition(glm::vec3 position)
    {
        m_lightPosition = position;
    }

    glm::vec3 Light::getPosition()
    {
        return m_lightPosition;
    }
}