#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Umu
{
    class Light
    {
        public:
            Light(glm::vec3 position);
            void setPosition(glm::vec3 position);
            glm::vec3 getPosition();
        private:
            glm::vec3 m_lightPosition;
    };
}