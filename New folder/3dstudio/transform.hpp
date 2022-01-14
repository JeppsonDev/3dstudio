#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Umu
{
    class Transform
    {
        public:
            Transform();
            void translate(glm::vec3 translation);
            void rotate(glm::vec3 angle, float rad);
            void scale(glm::vec3 scale);
            glm::mat4 getMatrix();
        private:
            glm::mat4 m_modelMatrix;
    };
}