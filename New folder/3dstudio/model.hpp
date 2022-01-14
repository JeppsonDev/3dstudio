#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.hpp"
#include "mesh.hpp"
#include "openglinput.hpp"
#include <vector>
#include "texture2d.hpp"
#include "gui.hpp"

using namespace glm;

namespace Umu 
{
    class Model
    {
        public:
            Model(std::vector<Mesh*> meshes, Shader *shader);
            Model(std::vector<Mesh*> meshes, Texture2D *texture, Shader *shader);
            ~Model(void);

            Mesh *getMesh(int i);
            int getMeshNum();
            std::vector<Mesh*> getMeshes();
            Shader *getShader();
            bool hasTextureCoordinates();
            Texture2D *getTexture();
        private:
            std::vector<Mesh*> m_pMeshes;
            Shader *m_pShader;
            Texture2D *m_pTexture;

            void onTextureToggle(OnTextureToggle event);
            void onTextureOpen(OnTextureOpen event);
    };
}