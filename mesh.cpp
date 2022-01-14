#include "mesh.hpp"

namespace Umu 
{
    Mesh::Mesh(std::vector<float> vertices, std::vector<uint> indices, std::vector<float> normals, std::vector<float> textureCoordinates, std::vector<Material*> materials)
    {
        m_vertices = vertices;
        m_indices = indices;
        m_normals = normals;
        m_textureCoordinates = textureCoordinates;
        m_materials = materials;

        prepare();
    }

    Mesh::Mesh(std::vector<float> vertices, std::vector<float> normals, std::vector<float> textureCoordinates)
    {
        m_vertices = vertices;
        m_normals = normals;
        m_textureCoordinates = textureCoordinates;

        Material *m_material = new Material();
        m_material->ambient = glm::vec3(0.6627f, 0.6627f, 0.6627f);
        m_material->diffuse = glm::vec3(0.01176f, 0.01176, 0.01176f);
        m_material->specular = glm::vec3(0.9058f, 0.9058f, 0.9058f);
        m_material->shininess = 1.0;

        m_materials.push_back(m_material);
        prepare();   
    }
    
    Mesh::Mesh(std::vector<float> vertices)
    {
        m_vertices = vertices;
        Material *m_material = new Material();
        m_material->ambient = glm::vec3(0.6627f, 0.6627f, 0.6627f);
        m_material->diffuse = glm::vec3(0.01176f, 0.01176, 0.01176f);
        m_material->specular = glm::vec3(0.9058f, 0.9058f, 0.9058f);
        m_material->shininess = 1.0;
        
        m_materials.push_back(m_material);

        prepare();   
    }

    Mesh::~Mesh()
    {
        for(int i = 0; i < getMaterialNum(); i++)
        {
            delete m_materials[i];
        }

        m_materials.clear();
    }

    //------------------------------------PUBLIC STATIC------------------------------------------//
    std::vector<Mesh*> Mesh::load(std::string pathToFile)
    {
        AssimpResult result = AssimpLoader::load(pathToFile);
        std::vector<Mesh*> meshes;

        if(fileExists(pathToFile))
        {
            for(uint i = 0; i < result.meshes.size(); i++)
            {
                meshes.push_back(new Mesh(result.meshes[i].vertices, result.meshes[i].indices, result.meshes[i].normals, result.meshes[i].textureCoordinates, result.meshes[i].materials));
            }

            std::cout << pathToFile << " loaded" << std::endl;
        }
        else
        {
            std::cout << "File not found" << std::endl;
        }     

        return meshes;
    }

    std::vector<Mesh*> Mesh::loadPlane()
    {
        std::vector<float> planeVertices;
        planeVertices.push_back(25.0f);
        planeVertices.push_back(-0.5f);
        planeVertices.push_back(25.0f);

        planeVertices.push_back(-25.0f);
        planeVertices.push_back(-0.5f);
        planeVertices.push_back(25.0f);

        planeVertices.push_back(-25.0f);
        planeVertices.push_back(-0.5f);
        planeVertices.push_back(-25.0f);

        planeVertices.push_back(25.0f);
        planeVertices.push_back(-0.5f);
        planeVertices.push_back(25.0f);

        planeVertices.push_back(-25.0f);
        planeVertices.push_back(-0.5f);
        planeVertices.push_back(-25.0f);

        planeVertices.push_back(25.0f);
        planeVertices.push_back(-0.5f);
        planeVertices.push_back(-25.0f);

        std::vector<float> planeNormals;
        planeNormals.push_back(0.0f);
        planeNormals.push_back(1.0f);
        planeNormals.push_back(0.0f);

        planeNormals.push_back(0.0f);
        planeNormals.push_back(1.0f);
        planeNormals.push_back(0.0f);

        planeNormals.push_back(0.0f);
        planeNormals.push_back(1.0f);
        planeNormals.push_back(0.0f);

        planeNormals.push_back(0.0f);
        planeNormals.push_back(1.0f);
        planeNormals.push_back(0.0f);

        planeNormals.push_back(0.0f);
        planeNormals.push_back(1.0f);
        planeNormals.push_back(0.0f);

        planeNormals.push_back(0.0f);
        planeNormals.push_back(1.0f);
        planeNormals.push_back(0.0f);

        std::vector<float> texCoords;
        texCoords.push_back(25.0f);
        texCoords.push_back(0.0f);

        texCoords.push_back(0.0f);
        texCoords.push_back(0.0f);
        
        texCoords.push_back(0.0f);
        texCoords.push_back(25.0f);

        texCoords.push_back(25.0f);
        texCoords.push_back(0.0f);

        texCoords.push_back(0.0f);
        texCoords.push_back(25.0f);

        texCoords.push_back(25.0f);
        texCoords.push_back(25.0f);

        std::vector<Mesh*> meshes;
        meshes.push_back(new Mesh(planeVertices, planeNormals, texCoords));

        return meshes;
    }

    //-----------------------------------------PUBLIC------------------------------------------//
    void Mesh::render() 
    {
        bindVAO();
        
        if(m_indices.size() > 0)
        {
            glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));    
        }
        else
        {
            //Draw the plane
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        unbindVAO();
    }

    void Mesh::bindVAO()
    {
        glBindVertexArray(m_vao);
    }

    void Mesh::unbindVAO()
    {
        glBindVertexArray(0);
    }

    bool Mesh::hasMaterials()
    {
        return m_materials.size() > 0;
    }

    Material *Mesh::getMaterial(int i)
    {
        return m_materials[i];
    }

    int Mesh::getMaterialNum()
    {
        return m_materials.size();
    }

    float Mesh::getVertex(int i)
    {
        return m_vertices[i];
    }

    int Mesh::getVertexNum()
    {
        return m_vertices.size();
    }

    //-----------------------------------------PRIVATE------------------------------------------//
    void Mesh::prepare()
    {
        //Gen VAO
        glGenVertexArrays(1, &m_vao);

        //Bind VAO
        bindVAO();
        
        //Gen buffers
        glGenBuffers( 1, &m_vBuffer);
        glBindBuffer( GL_ARRAY_BUFFER, m_vBuffer);

        if(m_indices.size() > 0)
        {
            glGenBuffers(1, &m_iBuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBuffer);
        }

        //Get the lengths
        size_t vSize = m_vertices.size()*sizeof(float);
        size_t nSize = m_normals.size()*sizeof(float);
        size_t tSize = m_textureCoordinates.size()*sizeof(float);

        //Get the offset
        int offset = vSize;
        offset += nSize > 0 ? nSize : 0;
        offset += tSize > 0 ? tSize : 0;

        //Fill the buffers
        glBufferData(GL_ARRAY_BUFFER, offset, NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, m_vertices.data()); 
        
        //Vertex Positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glEnableVertexAttribArray(0);

        if(nSize > 0)
        {
            //Fill normals subdata
            glBufferSubData(GL_ARRAY_BUFFER, vSize, nSize, m_normals.data());

            //Normals
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0 + vSize)); 
            glEnableVertexAttribArray(1);
        }

        if(tSize > 0)
        {
            //Fill textuers subdata
            glBufferSubData(GL_ARRAY_BUFFER, vSize + nSize, tSize, m_textureCoordinates.data()); 

            //Texture coordinates
            glEnableVertexAttribArray(2);	
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0 + vSize + nSize));   
        }

        if(m_indices.size() > 0)
        {
            //Fill indicies buffer
            size_t iSize = m_indices.size()*sizeof(unsigned int); 
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, m_indices.data(), GL_STATIC_DRAW);
        }

        //Unbind VAO
        unbindVAO();
    }
}