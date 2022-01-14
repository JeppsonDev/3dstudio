/**
 * @file transform.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 * @brief The transform class
 * @version 0.1
 * @date 2022-01-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Umu
{
    class Transform
    {
        public:
            /**
             * @brief Construct a new Transform object
             * 
             */
            Transform();

            /**
             * @brief Translates the object
             * 
             * @param translation 
             */
            void translate(glm::vec3 translation);

            /**
             * @brief Rotates the object
             * 
             * @param angle 
             * @param rad 
             */
            void rotate(glm::vec3 angle, float rad);

            /**
             * @brief scales the object
             * 
             * @param scale 
             */
            void scale(glm::vec3 scale);

            /**
             * @brief Gets Matrix
             * 
             * @return glm::mat4 
             */
            glm::mat4 getMatrix();

            /**
             * @brief Sets Matrix
             * 
             * @param mat 
             */
            void setMatrix(glm::mat4 mat);
        private:
            glm::mat4 m_modelMatrix;
    };
}