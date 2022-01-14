/**
 * @file assimp.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 *
 * @brief The class responsible for loading models into the program
 *
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <assimp/cimport.h>

#include <iostream>
#include <stdint.h>
#include <vector>

#include "material.h"

namespace Umu
{
    /**
     * @brief Temporary data which holds an entire mesh
     * 
     */
    struct MeshData
    {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::vector<float> normals;
        std::vector<float> textureCoordinates;
        std::vector<Material*> materials;
    };

    /**
     * @brief The result of the assimp model loading
     * 
     */
    struct AssimpResult
    {
        std::vector<MeshData> meshes;
    };

    class AssimpLoader
    {
        public:
            /**
             * @brief Loads a model
             * 
             * @param file 
             * @return AssimpResult 
             */
            static AssimpResult load(std::string file);

            /**
             * @brief prints debug data for the loading
             * 
             */
            static void print(void);
        private:
            /**
             * @brief Starts the assimp process
             * 
             */
            static void processStart();

            /**
             * @brief Processes every model in the assimp scene
             * 
             * @return true 
             * @return false 
             */
            static bool processModels();

            /**
             * @brief Process every mesh from model
             * 
             */
            static void processMeshes();

            /**
             * @brief Process every mesh
             * 
             * @param mesh 
             * @return MeshData 
             */
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