#include "assimp.hpp"

namespace Umu
{
    //TODO: Again wtf bro

    Assimp::Importer AssimpLoader::m_importer;
    const aiScene *AssimpLoader::m_pScene;
    const aiNode *AssimpLoader::modelNode;
    std::vector<const aiNode*> AssimpLoader::m_aiNodeBuffer;
    std::vector<float> AssimpLoader::vertices;
    std::vector<unsigned int> AssimpLoader::indices;
    std::vector<float> AssimpLoader::normals;
    std::vector<float> AssimpLoader::textureCoordinates;
    AssimpResult AssimpLoader::outResult;
    std::vector<MeshData> AssimpLoader::meshes;
    static int meshesProcessed = 0;
    //-----------------------------------------PUBLIC------------------------------------------//

    AssimpResult AssimpLoader::load(std::string file)
    {
        //TODO: Wtf bro
        m_aiNodeBuffer.clear();
        vertices.clear();
        indices.clear();
        normals.clear();
        meshes.clear();
        textureCoordinates.clear();
        meshesProcessed = 0;

        m_pScene = m_importer.ReadFile(file, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_FlipUVs | aiProcess_PreTransformVertices | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_FixInfacingNormals | aiProcess_FindInvalidData | aiProcess_ValidateDataStructure);

        if (!m_pScene)
        {
            return {};
        }
        else
        {
            processStart();
        }

        outResult.meshes = meshes;

        for(uint i = 0; i < outResult.meshes.size(); i++)
        {
            for(uint j = 0; j < outResult.meshes[i].normals.size(); j++)
            {
                std::cout << "Normal[" << i << "," << j << "]: " << outResult.meshes[i].normals[j] << std::endl;
            }

            //std::cout << "Normls: " << outResult.meshes[i].normals.size() << std::endl;
        }

        return outResult;
    }

    void AssimpLoader::print(void)
    {
        std::cout << "" << std::endl;  
        std::cout << "Num meshes: " << meshes.size() << std::endl;
        std::cout << "" << std::endl;  

        for(uint i = 0; i < meshes.size(); i++)
        {
            std::cout << "Mesh[" << i << "]:" << std::endl;
            std::cout << "Num vertices: " << meshes[i].vertices.size() << std::endl;
            std::cout << "Num indicies: " << meshes[i].indices.size() << std::endl;
        }
    }

    //-----------------------------------------PRIVATE------------------------------------------//
    
    void AssimpLoader::processStart()
    {
        bool run = true;
        
        m_aiNodeBuffer.push_back(m_pScene->mRootNode);

        while(run)
        {
            run = processModels();
        }

        processMeshes();
    }

    bool AssimpLoader::processModels()
    {
        for(unsigned int i = 0; i < m_aiNodeBuffer.size(); i++)
        {
            modelNode = m_aiNodeBuffer.at(i);
            if(modelNode->mNumChildren > 0)
            {
                for(unsigned int j = 0; j < modelNode->mNumChildren; j++) 
                {
                    m_aiNodeBuffer.push_back(modelNode->mChildren[j]);
                }
            }
            else
            {
                return false;
            }
        }

        return true;
    }

    void AssimpLoader::processMeshes()
    {
        for(unsigned int i = 0; i < m_aiNodeBuffer.size(); i++)
        {
            modelNode = m_aiNodeBuffer.at(i);

            if(modelNode->mNumMeshes > 0)
            {
                for(unsigned int j = 0; j < modelNode->mNumMeshes; j++) 
                {
                    meshes.push_back(processMesh(m_pScene->mMeshes[meshesProcessed]));
                    
                    //TODO: Fix this.. loop m_pScene->mNumMeshes instead or something
                    meshesProcessed++;
                }
            }
        }
    }

    MeshData AssimpLoader::processMesh(const aiMesh *mesh)
    {
        vertices.clear();
        normals.clear();
        textureCoordinates.clear();
        indices.clear();

        for(unsigned int v = 0; v < mesh->mNumVertices; v++)
        {
            float x = mesh->mVertices[v].x;
            float y = mesh->mVertices[v].y;
            float z = mesh->mVertices[v].z;

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            if(mesh->HasNormals())
            {
                normals.push_back(mesh->mNormals[v].x);
                normals.push_back(mesh->mNormals[v].y);
                normals.push_back(mesh->mNormals[v].z);
            }

            if(mesh->HasTextureCoords(0))
            {
                textureCoordinates.push_back(mesh->mTextureCoords[0][v].x);
                textureCoordinates.push_back(mesh->mTextureCoords[0][v].y);
            }
            else 
            {
                textureCoordinates.push_back(0);
                textureCoordinates.push_back(0);
            }
        }

        for(unsigned int f = 0; f < mesh->mNumFaces; f++)
        {
            aiFace face = mesh->mFaces[f];

            for(unsigned int i = 0; i < face.mNumIndices; i++)
            {
                indices.push_back(face.mIndices[i]);
            }
        }

        std::cout << "Num vertices: " << vertices.size() << std::endl;
        std::cout << "Num indicies: " << indices.size() << std::endl;

        return {vertices, indices, normals, textureCoordinates};
    }
}