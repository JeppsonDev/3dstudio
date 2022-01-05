#include "model.hpp"

namespace Umu
{
    Model::Model(std::vector<Mesh*> meshes, Shader *shader)
    {
        m_pMeshes = meshes;
        m_pShader = shader;
        m_pTexture = new Texture2D();
    }

    Model::Model(std::vector<Mesh*> meshes, Texture2D *texture, Shader *shader)
    {
        m_pMeshes = meshes;
        m_pShader = shader;
        m_pTexture = texture;

        //TODO: This event currently runs twice
        Gui::getOnTextureToggle()->registerEvent(std::bind(&Model::onTextureToggle, this, std::placeholders::_1));
        
        Gui::getOnTextureOpen()->registerEvent(std::bind(&Model::onTextureOpen, this, std::placeholders::_1));
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
        Gui::getOnTextureOpen()->clearEvents();
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

    Texture2D *Model::getTexture()
    {
        return m_pTexture;
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
            m_pTexture->show();
            //m_pTexture->bind(0);
        }
        else
        {
            m_pTexture->hide();
            //m_pTexture->unbind();
        }
    }

    void Model::onTextureOpen(OnTextureOpen event)
    {
        if(m_pTexture != nullptr)
        {
            delete m_pTexture;
        }

        m_pTexture = new Texture2D(event.filepath);
        m_pTexture->show();

        //TODO: This event currently runs twice
        Gui::getOnTextureToggle()->registerEvent(std::bind(&Model::onTextureToggle, this, std::placeholders::_1));
    }
}