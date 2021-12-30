#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <assimp/cimport.h>

#include <iostream>
#include <stdint.h>
#include <vector>
#include "mesh.hpp"

namespace Umu
{
    struct MeshData
    {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::vector<float> normals;
        std::vector<float> textureCoordinates;
    };

    struct AssimpResult
    {
        std::vector<MeshData> meshes;
    };

    class AssimpLoader
    {
        public:
            static AssimpResult load(std::string file);
            static void print(void);
        private:
            static void processStart();
            static bool processModels();
            static void processMeshes();
            static MeshData processMesh(const aiMesh *mesh);
        private:
            static Assimp::Importer m_importer;
            static const aiScene *m_pScene;
            static const aiNode *modelNode;
            static std::vector<const aiNode*> m_aiNodeBuffer;
            static std::vector<float> vertices;
            static std::vector<unsigned int> indices;
            static std::vector<float> normals;
            static std::vector<float> textureCoordinates;
            static std::vector<MeshData> meshes;
            static AssimpResult outResult;
    };
}