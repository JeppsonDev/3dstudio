#include "model.hpp"

namespace Umu
{
    Model::Model(std::vector<Mesh*> meshes)
    {
        m_pMeshes = meshes;
        m_pTexture = new Texture2D();

        Gui::getOnTextureOpen()->clearEvents();
        Gui::getOnTextureOpen()->registerEvent(std::bind(&Model::onTextureOpen, this, std::placeholders::_1));
    }

    Model::Model(std::vector<Mesh*> meshes, Texture2D *texture)
    {
        m_pMeshes = meshes;
        m_pTexture = texture;
        Gui::getOnTextureToggle()->registerEvent(std::bind(&Model::onTextureToggle, this, std::placeholders::_1));
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

    Texture2D *Model::getTexture()
    {
        return m_pTexture;
    }

    //-----------------------------------------PRIVATE------------------------------------------//
    void Model::onTextureToggle(OnTextureToggle event)
    {
        if(event.textureShow)
        {
            m_pTexture->show();
        }
        else
        {
            m_pTexture->hide();
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
        Gui::getOnTextureToggle()->registerEvent(std::bind(&Model::onTextureToggle, this, std::placeholders::_1));
    }
}