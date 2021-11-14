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

#define BUFFER_OFFSET(i) (reinterpret_cast<char*>(0 + (i)))

using namespace glm;

namespace Umu 
{
    class Shader
    {
        public:
            Shader(std::string vshader, std::string fshader);
            ~Shader(void);

            void start();
            void bindVAO();
            void prepareReadData();
            void unbindVAO();
            void stop();

        protected:
            GLuint m_program;
            //TODO: write m_ infront of these or potentially figure out where to place them eleswhere
            //should probably not be placed in base shader class 
            GLuint vao;
            GLuint vBuffer;
            GLuint iBuffer;
            GLuint locVertices;

        private:
            GLuint initProgram(std::string vshader, std::string fshader);
            std::string readShaderSource(const std::string shaderFile);
    };
}