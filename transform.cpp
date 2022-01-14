#include "transform.hpp"

namespace Umu
{
    Transform::Transform()
    {
        m_modelMatrix = glm::identity<glm::mat4>();
    }

    //-----------------------------------------PUBLIC------------------------------------------//
    void Transform::translate(glm::vec3 translation)
    {
        m_modelMatrix = glm::translate(glm::identity<glm::mat4>(), translation) * m_modelMatrix;
    }

    void Transform::rotate(glm::vec3 angle, float rad)
    {
        m_modelMatrix = glm::rotate(m_modelMatrix, rad, angle);
    }

    void Transform::scale(glm::vec3 scale)
    {
        m_modelMatrix = glm::scale(m_modelMatrix, scale);
    }

    void Transform::setMatrix(glm::mat4 mat)
    {
        m_modelMatrix = mat;
    }

    glm::mat4 Transform::getMatrix()
    {
        return m_modelMatrix;
    }
}