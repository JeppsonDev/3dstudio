#include "assimp.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

namespace Umu
{
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
        }

        for(unsigned int f = 0; f < mesh->mNumFaces; f++)
        {
            aiFace face = mesh->mFaces[f];

            for(unsigned int i = 0; i < face.mNumIndices; i++)
            {
                indices.push_back(face.mIndices[i]);
            }
        }

        if(textureCoordinates.size() <= 0)
        {
            float r = 50;

            float pi = 3.14159265359;

            glm::vec3 p;
            
            for(unsigned int i = 0; i < vertices.size(); i += 3)
            {
                glm::vec3 v0 = glm::vec3(vertices[i], vertices[i+1], vertices[i+2]);
                glm::vec3 N = glm::vec3(normals[i], normals[i+1], normals[i+2]);

                float a = glm::dot(N, N); 
                float b = 2*(glm::dot(v0, N));
                float c = glm::dot(v0, v0) - std::pow(r, 2);
                float delta = std::pow(b,2) - (4*a*c);

                if(delta < 0)
                {
                    continue;
                }

                float q = -(1/2) * (b + glm::sign(b) * std::sqrt(delta));
                float d1 = q/a;
                float d2 = c/q;

                if(d1 >= 0)
                {
                    p = glm::normalize(v0 + d1 * N) * r;
                }
                else
                {
                    p = glm::normalize(v0 + d2 * N) * r;
                }
                
                float s = (std::acos(p.x/r))/pi;
                float t = ((std::atan(p.z/p.y))/pi) + 1/2;

                textureCoordinates.push_back(s);
                textureCoordinates.push_back(t);
            }
        }

        

        std::vector<Material*> outMaterials;

        Material *outMaterial1 = new Material();
        outMaterial1->ambient = glm::vec3(0.6627f, 0.6627f, 0.6627f);
        outMaterial1->diffuse = glm::vec3(0.01176f, 0.01176, 0.01176f);
        outMaterial1->specular = glm::vec3(0.9058f, 0.9058f, 0.9058f);
        outMaterial1->shininess = 1.0;

        outMaterials.push_back(outMaterial1);

        if(m_pScene->HasMaterials())
        {
            aiMaterial* mat = m_pScene->mMaterials[mesh->mMaterialIndex];
            
            Material *outMaterial2 = new Material();

            aiColor3D ambient;
            if(mat->Get(AI_MATKEY_COLOR_AMBIENT, ambient) == AI_SUCCESS)
            {
                outMaterial2->ambient.x = ambient.r;
                outMaterial2->ambient.y = ambient.g;
                outMaterial2->ambient.z = ambient.b;
            }

            aiColor3D diffuse;
            if(mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse) == AI_SUCCESS)
            {
                outMaterial2->diffuse.x = diffuse.r;
                outMaterial2->diffuse.y = diffuse.g;
                outMaterial2->diffuse.z = diffuse.b;
            }

            aiColor3D specular;
            if(mat->Get(AI_MATKEY_COLOR_SPECULAR, specular) == AI_SUCCESS)
            {
                outMaterial2->specular.x = specular.r;
                outMaterial2->specular.y = specular.g;
                outMaterial2->specular.z = specular.b;
            }

            outMaterials.push_back(outMaterial2);
        }

        for(unsigned int i = 0; i < outMaterials.size(); i++)
        {
            if(outMaterials[i]->ambient.x <= 0)
            {
                outMaterials[i]->ambient.x = 0.6627f;
            }
            if(outMaterials[i]->ambient.y <= 0)
            {
                outMaterials[i]->ambient.y = 0.6627f;
            }
            if(outMaterials[i]->ambient.z <= 0)
            {
                outMaterials[i]->ambient.z = 0.6627f;
            }

            if(outMaterials[i]->diffuse.x <= 0)
            {
                outMaterials[i]->diffuse.x = 0.01176f;
            }
            if(outMaterials[i]->diffuse.y <= 0)
            {
                outMaterials[i]->diffuse.y = 0.01176f;
            }
            if(outMaterials[i]->diffuse.z <= 0)
            {
                outMaterials[i]->diffuse.z = 0.01176f;
            }

            if(outMaterials[i]->specular.x <= 0)
            {
                outMaterials[i]->specular.x = 0.9058f;
            }
            if(outMaterials[i]->specular.y <= 0)
            {
                outMaterials[i]->specular.y = 0.9058f;
            }
            if(outMaterials[i]->specular.z <= 0)
            {
                outMaterials[i]->specular.z = 0.9058f;
            }
        }

        std::cout << "{" << std::endl;
        std::cout << "\tNum vertices: " << vertices.size() << std::endl;
        std::cout << "\tNum indicies: " << indices.size() << std::endl;
        std::cout << "\tNum normals: " << normals.size() << std::endl;
        std::cout << "\tNum texture coords: " << textureCoordinates.size() << std::endl;
        std::cout << "}" << std::endl;

        return {vertices, indices, normals, textureCoordinates, outMaterials};
    }
}