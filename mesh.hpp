#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.hpp"
#include "openglinput.hpp"

using namespace glm;

#define BUFFER_OFFSET(i) (reinterpret_cast<char*>(0 + (i)))

namespace Umu 
{
    class Mesh
    {
        public:
            Mesh(std::vector<float> vertices, std::vector<unsigned int> indices);
            ~Mesh(void);

            void render();
            void translate(vec3 translation);
            void rotate(vec3 angle, float rad);
            void prepareForRender(Shader *shader);
            mat4 getTransformationMatrix();

        private:
            void fillVertexBuffer();
            void fillIndexBuffer();

        private:
            std::vector<float> m_vertices;
            std::vector<unsigned int> m_indices;
            mat4 m_transformationMatrix;
    };
}