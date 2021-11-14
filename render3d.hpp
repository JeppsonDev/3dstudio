#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
#include <vector>
#include <stdint.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "teddyshader.hpp"
#include "mesh.hpp"

namespace Umu 
{
    class Render3D
    {
        public:
            Render3D(void);
            ~Render3D(void);

            void render();
            void prepare(std::vector<float> vertices, std::vector<unsigned int> indices);

        private:
            TeddyShader *m_pMainShader;
            Mesh *m_pMainMesh;

    };
}