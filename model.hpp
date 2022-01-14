/**
 * @file model.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)

 * @brief The class representing a model
 
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "mesh.hpp"
#include "openglinput.hpp"
#include "texture2d.hpp"
#include "gui.hpp"

using namespace glm;

namespace Umu 
{
    class Model
    {
        public:
            /**
             * @brief Construct a new Model object
             * 
             * @param meshes 
             */
            Model(std::vector<Mesh*> meshes);

            /**
             * @brief Construct a new Model object
             * 
             * @param meshes 
             * @param texture 
             */
            Model(std::vector<Mesh*> meshes, Texture2D *texture);

            /**
             * @brief Destroy the Model object
             * 
             */
            ~Model(void);

            /**
             * @brief Gets Mesh from index i
             * 
             * @param i 
             * @return Mesh* 
             */
            Mesh *getMesh(int i);

            /**
             * @brief Gets Mesh Num
             * 
             * @return int 
             */
            int getMeshNum();

            /**
             * @brief Gets Meshes
             * 
             * @return std::vector<Mesh*> 
             */
            std::vector<Mesh*> getMeshes();

            /**
             * @brief Gets Shader
             * 
             * @return Shader* 
             */
            Shader *getShader();

            /**
             * @brief Gets Texture
             * 
             * @return Texture2D* 
             */
            Texture2D *getTexture();
        private:
            std::vector<Mesh*> m_pMeshes;
            Shader *m_pShader;
            Texture2D *m_pTexture;

            /**
             * @brief On texture toggle event
             * 
             * @param event 
             */
            void onTextureToggle(OnTextureToggle event);

            /**
             * @brief On texture open event
             * 
             * @param event 
             */
            void onTextureOpen(OnTextureOpen event);
    };
}