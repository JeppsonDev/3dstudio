#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <cmath>
#include <vector>
#include <stdint.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>

#define BUFFER_OFFSET(i) (reinterpret_cast<char*>(0 + (i)))

using namespace glm;

namespace Umu 
{
    class Shader
    {
        public:
            Shader(std::string vshader, std::string fshader);
            Shader();
            ~Shader(void);

            void setMat4(std::string uniformKey, mat4 modelMatrix);
            void setVec3(std::string uniformKey, vec3 vector);
            void setFloat(std::string uniformKey, float val);
            void setInt(std::string uniformKey, int val);
            
            GLuint getProperty(std::string key);

            void start();
            void stop();

        protected:
            std::unordered_map<std::string, GLuint> m_properties;
            GLuint m_program;
            GLuint initProgram(std::string vshader, std::string fshader);
            void checkCompileErrors(GLuint shader, std::string type);
            std::string readShaderSource(const std::string shaderFile);
    };
}