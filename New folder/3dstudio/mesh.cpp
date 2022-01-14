#include "mesh.hpp"

namespace Umu 
{
    Mesh::Mesh(std::vector<float> vertices, std::vector<uint> indices, std::vector<float> normals, std::vector<float> textureCoordinates)
    {
        m_vertices = vertices;
        m_indices = indices;
        m_normals = normals;
        m_textureCoordinates = textureCoordinates;

        prepare();
        
    }

    Mesh::~Mesh()
    {
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
                meshes.push_back(new Mesh(result.meshes[i].vertices, result.meshes[i].indices, result.meshes[i].normals, result.meshes[i].textureCoordinates));
            }

            std::cout << pathToFile << " loaded" << std::endl;
        }
        else
        {
            std::cout << "File not found" << std::endl;
        }     

        return meshes;
    }

    //-----------------------------------------PUBLIC------------------------------------------//

    void Mesh::render() 
    {
        bindVAO();
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
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

    float Mesh::getVertex(int i)
    {
        return m_vertices[i];
    }

    int Mesh::getVertexNum()
    {
        return m_vertices.size();
    }

    bool Mesh::hasTextureCoordinates()
    {
        return m_textureCoordinates.size() > 0;
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

        glGenBuffers(1, &m_iBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBuffer);

        //Fill buffers
        size_t vSize = m_vertices.size()*sizeof(float);
        size_t nSize = m_normals.size()*sizeof(float);
        size_t tSize = m_textureCoordinates.size()*sizeof(float);

        glBufferData(GL_ARRAY_BUFFER, vSize + nSize + tSize, NULL, GL_STATIC_DRAW); 
        glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, m_vertices.data()); 
        glBufferSubData(GL_ARRAY_BUFFER, vSize, nSize, m_normals.data());
        glBufferSubData(GL_ARRAY_BUFFER, vSize + nSize, tSize, m_textureCoordinates.data());

        size_t iSize = m_indices.size()*sizeof(unsigned int); 
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, m_indices.data(), GL_STATIC_DRAW);

        //Vertex Positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glEnableVertexAttribArray(0);

        //Normals
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vSize)); 
        glEnableVertexAttribArray(1);

        //Texture coordinates
        glEnableVertexAttribArray(2);	
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vSize + nSize));

        //Unbind VAO
        unbindVAO();
    }
}