#include "assimp.hpp"

namespace Umu
{
    AssimpLoader::AssimpLoader()
    {

    }

    AssimpLoader::~AssimpLoader(void)
    {
        std::cout << "Destroyed AssimpLoader.cpp" << std::endl;
    }

    //-----------------------------------------PUBLIC------------------------------------------//

    bool AssimpLoader::load(std::string file)
    {
        m_pScene = m_importer.ReadFile(file, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate);

        if (!m_pScene)
        {
            return false;
        }
        else
        {
            processStart();
        }
        return true;
    }

    void AssimpLoader::print(void)
    {
        std::cout << "" << std::endl;  
        std::cout << "Num meshes: " << m_pScene->mNumMeshes << std::endl;
        std::cout << "Num vertices: " << vertices.size() << std::endl;
        std::cout << "Num indicies: " << indices.size() << std::endl;
        std::cout << "" << std::endl;  


        for(unsigned int v = 0; v < vertices.size(); v += 3)
        {
            std::cout << "  V[" << v << "].x: " << vertices.at(v) << std::endl;
            std::cout << "  V[" << v << "].y: " << vertices.at(v+1) << std::endl;
            std::cout << "  V[" << v << "].z: " << vertices.at(v+2) << std::endl;
            std::cout << "" << std::endl;
        }

        for(unsigned int v = 0; v < indices.size(); v += 3)
        {
            std::cout << "  I[" << v << "].x: " << indices.at(v) << std::endl;
            std::cout << "  I[" << v << "].y: " << indices.at(v+1) << std::endl;
            std::cout << "  I[" << v << "].z: " << indices.at(v+2) << std::endl;
            std::cout << "" << std::endl;
        }
    }

    std::vector<float> AssimpLoader::getVertices(void)
    {
        return vertices;
    }

    std::vector<unsigned int> AssimpLoader::getIndicies(void)
    {
        return indices;
    }

    //-----------------------------------------PRIVATE------------------------------------------//
    
    void AssimpLoader::processStart(void)
    {
        bool run = true;
        
        m_aiNodeBuffer.push_back(m_pScene->mRootNode);

        while(run)
        {
            run = processModels();
        }

        processMeshes();
    }

    bool AssimpLoader::processModels(void)
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

    void AssimpLoader::processMeshes(void)
    {
        for(unsigned int i = 0; i < m_aiNodeBuffer.size(); i++)
        {
            modelNode = m_aiNodeBuffer.at(i);

            if(modelNode->mNumMeshes > 0)
            {
                for(unsigned int j = 0; j < modelNode->mNumMeshes; j++) 
                {
                    processMesh(m_pScene->mMeshes[j]);
                }
            }
        }
    }

    bool AssimpLoader::processMesh(const aiMesh *mesh)
    {
        for(unsigned int v = 0; v < mesh->mNumVertices; v++)
        {
            vertices.push_back(mesh->mVertices[v].x);
            vertices.push_back(mesh->mVertices[v].y);
            vertices.push_back(mesh->mVertices[v].z);

            //vertices.push_back(mesh->mNormals[v].x);
            //vertices.push_back(mesh->mNormals[v].y);
            //vertices.push_back(mesh->mNormals[v].z);

            if(mesh->HasTextureCoords(0))
            {
                //vertices.push_back(mesh->mTextureCoords[0][v].x);
                //vertices.push_back(mesh->mTextureCoords[0][v].y);
            }
            else 
            {
                //vertices.push_back(0);
                //vertices.push_back(0);
            }
        }

        for(unsigned int f = 0; f < mesh->mNumFaces; f++)
        {
            aiFace face = mesh->mFaces[f];

            indices.push_back(face.mIndices[0]);
            indices.push_back(face.mIndices[1]);
            indices.push_back(face.mIndices[2]);
        }

        return true;
    }
}