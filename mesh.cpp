#include "mesh.hpp"

namespace Umu 
{
    Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices)
    {
        m_transformationMatrix = identity<mat4>();
        m_vertices = vertices;
        m_indices = indices;
    }

    Mesh::~Mesh()
    {

    }

    //-----------------------------------------PUBLIC------------------------------------------//

    //TODO: TEMP: This should be moved to some sort of "3Dstudio" class where 3D models can
    // be moved around or something

    bool r;
    bool t;

    void Mesh::render()
    {
        //TODO: TEMP: Change this to an update loop eventually?
        if(OpenGLInput::isKeyPressed("up"))
        {
            if(t)
                translate(vec3(0,.1f,0));
            else if(r)
                rotate(vec3(1.0f,0.0f,0.0f), 0.1f);
        }

        if(OpenGLInput::isKeyPressed("down"))
        {
            if(t)
                translate(vec3(0,-.1f,0));
            else if(r)
                rotate(vec3(1.0f,0.0f,0), -0.1f);
        }

        if(OpenGLInput::isKeyPressed("right"))
        {
            if(t)
                translate(vec3(.1f,0,0));
            else if(r)
                rotate(vec3(0,0,1.0f), -0.1f);
        }

        if(OpenGLInput::isKeyPressed("left"))
        {
            if(t)
                translate(vec3(-.1f,0,0));
            else if(r)
                rotate(vec3(0,0,1.0f), 0.1f);
        }

        if(OpenGLInput::isKeyPressed("r"))
        {
            r = true;
            t = false;
        }

        if(OpenGLInput::isKeyPressed("t"))
        {
            r = false;
            t = true;
        }

        glDrawElements(GL_TRIANGLES, static_cast<int>(m_indices.size()), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
    }

    void Mesh::translate(vec3 translation)
    {
        m_transformationMatrix = glm::translate(m_transformationMatrix, translation);
    }

    void Mesh::rotate(vec3 angle, float rad)
    {
        m_transformationMatrix = glm::rotate(m_transformationMatrix, rad, angle);
    }

    void Mesh::prepareForRender(Shader *shader)
    {
        shader->start();
        shader->bindVAO();    
        shader->prepareReadData();
        fillVertexBuffer();
        fillIndexBuffer();
        shader->unbindVAO();
        shader->stop();
    }

    mat4 Mesh::getTransformationMatrix()
    {
        return m_transformationMatrix;
    }

    //-----------------------------------------PRIVATE------------------------------------------//
    
    void Mesh::fillVertexBuffer()
    {
        size_t vSize = m_vertices.size()*sizeof(float);

        glBufferData(GL_ARRAY_BUFFER, vSize, m_vertices.data(), GL_STATIC_DRAW);
    }

    void Mesh::fillIndexBuffer()
    {
        size_t iSize = m_indices.size()*sizeof(unsigned int);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, m_indices.data(), GL_STATIC_DRAW);
    }
}