#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
#include <vector>
#include <string>
#include <stdint.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "assimp.hpp"
#include "object.hpp"

namespace Umu 
{
    class Render3D
    {
        public:
            Render3D(void);
            ~Render3D(void);

            void render();
            void renderObject(Object *object);

            void add(Model *model);
            void loadModel(std::string filePath);
    };
}