#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.hpp"
#include "tools.h"

using namespace glm;

#define BUFFER_OFFSET(i) (reinterpret_cast<char*>(0 + (i)))

namespace Umu 
{

    class Mesh
    {
        public:
            Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> normals, std::vector<float> textureCoordinates);
            ~Mesh(void);

            static std::vector<Mesh*> load(std::string pathToFile);

            void render();
            void bindVAO();
            void unbindVAO();

            float getVertex(int i);
            int getVertexNum();
            bool hasTextureCoordinates();

        private:
            std::vector<float> m_vertices;
            std::vector<unsigned int> m_indices;
            std::vector<float> m_normals;
            std::vector<float> m_textureCoordinates;
            GLuint m_vao;
            GLuint m_vBuffer;
            GLuint m_iBuffer;

            void prepare();
    };
}