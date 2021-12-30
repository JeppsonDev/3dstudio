#include "model.hpp"

namespace Umu
{
    Model::Model(std::vector<Mesh*> meshes, Shader *shader)
    {
        m_pMeshes = meshes;
        m_pShader = shader;
    
        Gui::getOnTextureToggle()->registerEvent(std::bind(&Model::onTextureToggle, this, std::placeholders::_1));

        if(hasTextureCoordinates())
        {
            m_pTexture = new Texture2D("models/bricks.bmp");
            m_pTexture->bind(0);
            shader->setInt("u_Texture", 0);
        }
    }

    Model::~Model()
    {
        for(int i = 0; i < getMeshNum(); i++)
        {
            delete m_pMeshes[i];
        }

        m_pMeshes.clear();

        if(m_pTexture != nullptr)
        {
            delete m_pTexture;
        }

        Gui::getOnTextureToggle()->clearEvents();
    }

    //-----------------------------------------PUBLIC------------------------------------------//
    Mesh *Model::getMesh(int i)
    {
        return m_pMeshes[i];
    }

    int Model::getMeshNum()
    {
        return m_pMeshes.size();
    }

    std::vector<Mesh*> Model::getMeshes()
    {
        return m_pMeshes;
    }

    Shader *Model::getShader()
    {
        return m_pShader;
    }

    bool Model::hasTextureCoordinates()
    {
        for(uint i = 0; i < m_pMeshes.size(); i++)
        {
            if(m_pMeshes[i]->hasTextureCoordinates())
            {
                return true;
            }
        }
    }

    //-----------------------------------------PRIVATE------------------------------------------//
    void Model::onTextureToggle(OnTextureToggle event)
    {
        if(!hasTextureCoordinates())
        {
            return;
        }

        if(event.textureShow)
        {
            m_pTexture->bind(0);
        }
        else
        {
            m_pTexture->unbind();
        }
    }

}
//TODO: Implement this back in

        /*
        if(OpenGLInput::isKeyPressed("up"))
        {
            if(t)
                translate(vec3(0,.1f,0));
            else if(r)
                rotate(vec3(1.0f,0.0f,0.0f), 0.174532925f);
            else if(s)
                scale(vec3(1.0f, 1.1f, 1.0f));
        }

        if(OpenGLInput::isKeyPressed("down"))
        {
            if(t)
                translate(vec3(0,-.1f,0));
            else if(r)
                rotate(vec3(1.0f,0.0f,0), -0.174532925f);
            else if(s)
                scale(vec3(1.0f, 0.9f, 1.0f));
        }

        if(OpenGLInput::isKeyPressed("right"))
        {
            if(t)
                translate(vec3(.1f,0,0));
            else if(r)
                rotate(vec3(0.0f,1.0f,0.0f), -0.174532925f);
            else if(s)
                scale(vec3(1.1f, 1.0f, 1.0f));
        }

        if(OpenGLInput::isKeyPressed("left"))
        {
            if(t)
                translate(vec3(-.1f,0,0));
            else if(r)
                rotate(vec3(0.05f,1.0f,0.0f), 0.174532925f);
            else if(s)
                scale(vec3(0.9f, 1.0f, 1.0f));
        }

        if(OpenGLInput::isKeyPressed("r"))
        {
            r = true;
            t = false;
            s = false;
        }

        if(OpenGLInput::isKeyPressed("t"))
        {
            r = false;
            t = true;
            s = false;
        }

        if(OpenGLInput::isKeyPressed("s"))
        {
            r = false;
            t = false;
            s = true;
        }
*/
        /*
        m_pShader->start();
        m_pMesh->bindVAO();

        m_pMesh->render();
        m_pShader->setMat4("u_Model", m_modelMatrix);
        
        m_pMesh->unbindVAO();
        m_pShader->stop();
        */