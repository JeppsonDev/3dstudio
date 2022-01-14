/**
 * @file mesh.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 
 * @brief The class representing a mesh 

 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "tools.h"
#include "material.h"

using namespace glm;

#define BUFFER_OFFSET(i) (reinterpret_cast<char*>(0 + (i)))

namespace Umu 
{
    class Mesh
    {
        public:
            /**
             * @brief Construct a new Mesh object
             * 
             * @param vertices 
             * @param indices 
             * @param normals 
             * @param textureCoordinates 
             * @param materials 
             */
            Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> normals, std::vector<float> textureCoordinates, std::vector<Material*> materials);
            
            /**
             * @brief Construct a new Mesh object
             * 
             * @param vertices 
             * @param normals 
             * @param textureCoordinates 
             */
            Mesh(std::vector<float> vertices, std::vector<float> normals, std::vector<float> textureCoordinates);
            
            /**
             * @brief Construct a new Mesh object
             * 
             * @param vertices 
             */
            Mesh(std::vector<float> vertices);

            /**
             * @brief Destroy the Mesh object
             * 
             */
            ~Mesh(void);

            /**
             * @brief Loads a mesh from file
             * 
             * @param pathToFile 
             * @return std::vector<Mesh*> 
             */
            static std::vector<Mesh*> load(std::string pathToFile);

            /**
             * @brief Loads a plane mesh
             * 
             * @return std::vector<Mesh*> 
             */
            static std::vector<Mesh*> loadPlane();

            /**
             * @brief Renders the mesh
             * 
             */
            void render();

            /**
             * @brief Bind the mesh VAO
             * 
             */
            void bindVAO();

            /**
             * @brief Unbind the mesh VAO
             * 
             */
            void unbindVAO();

            /**
             * @brief Has materials
             * 
             * @return true
             * @return false
             */
            bool hasMaterials();

            /**
             * @brief Gets Material from index
             * 
             * @param i 
             * @return Material* 
             */
            Material *getMaterial(int i);

            /**
             * @brief Gets Material Num
             * 
             * @return int 
             */
            int getMaterialNum();

            /**
             * @brief Gets Vertex from index
             * 
             * @param i 
             * @return float 
             */
            float getVertex(int i);

            /**
             * @brief Gets Vertex Num
             * 
             * @return int 
             */
            int getVertexNum();

        private:
            std::vector<float> m_vertices;
            std::vector<unsigned int> m_indices;
            std::vector<float> m_normals;
            std::vector<float> m_textureCoordinates;
            std::vector<Material*> m_materials;
            GLuint m_vao;
            GLuint m_vBuffer;
            GLuint m_iBuffer;

            /**
             * @brief Prepares the mesh data for rendering
             * 
             */
            void prepare();
    };
}