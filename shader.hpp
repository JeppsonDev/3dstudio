/**
 * @file shader.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 *
 * @brief Class representing the shader
 *
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
#include <vector>
#include <stdint.h>
#include <unordered_map>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
            /**
             * @brief Construct a new Shader object
             * 
             * @param vshader 
             * @param fshader 
             */
            Shader(std::string vshader, std::string fshader);
            /**
             * @brief Construct a new Shader object
             * 
             */
            Shader();
            /**
             * @brief Destroy the Shader object
             * 
             */
            ~Shader(void);

            /**
             * @brief Sets Mat4
             * 
             * @param uniformKey 
             * @param modelMatrix 
             */
            void setMat4(std::string uniformKey, mat4 modelMatrix);
            
            /**
             * @brief Sets Vec3
             * 
             * @param uniformKey 
             * @param vector 
             */
            void setVec3(std::string uniformKey, vec3 vector);
            
            /**
             * @brief Sets Float
             * 
             * @param uniformKey 
             * @param val 
             */
            void setFloat(std::string uniformKey, float val);
            
            /**
             * @brief Sets Int
             * 
             * @param uniformKey 
             * @param val 
             */
            void setInt(std::string uniformKey, int val);
            
            /**
             * @brief Gets Property
             * 
             * @param key 
             * @return GLuint 
             */
            GLuint getProperty(std::string key);

            /**
             * @brief Starts the shader
             * 
             */
            void start();

            /**
             * @brief Stops the shader
             * 
             */
            void stop();

        protected:
            std::unordered_map<std::string, GLuint> m_properties;
            GLuint m_program;
            
            /**
             * @brief Initializes the program
             * 
             * @param vshader 
             * @param fshader 
             * @return GLuint 
             */
            GLuint initProgram(std::string vshader, std::string fshader);
            
            /**
             * @brief Reads the shader source
             * 
             * @param shaderFile 
             * @return std::string 
             */
            std::string readShaderSource(const std::string shaderFile);
    };
}