#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <assimp/cimport.h>

#include <iostream>
#include <stdint.h>
#include <vector>

namespace Umu
{
    class AssimpLoader
    {
        public:
            AssimpLoader(void);
            ~AssimpLoader(void);
            
            bool load(std::string file);
            void print(void);
            
            std::vector<float> getVertices();
            std::vector<unsigned int> getIndicies();
        private:
            void processStart(void);
            bool processModels(void);
            void processMeshes(void);
            bool processMesh(const aiMesh *mesh);
        private:
            Assimp::Importer m_importer;
            const aiScene *m_pScene;
            const aiNode *modelNode;

            std::vector<const aiNode*> m_aiNodeBuffer;
            
            std::vector<float> vertices;
            std::vector<unsigned int> indices;
    };
}