#include "object.hpp"
#include "gui.hpp"

namespace Umu
{
    Object::Object(int id, Model *model)
    {
        m_id = id;
        m_pModel = model;
        m_pTransform = new Transform();
        m_enabled = true;

        normalize(model->getMeshes(), m_pTransform);

        Gui::getOnUpdateMaterialObserver()->registerEvent(std::bind(&Object::onUpdateMaterialEvent, this, std::placeholders::_1));
    }

    Object::~Object()
    {
        std::cout << "Freeing Object" << std::endl;
        delete m_pModel;
        delete m_pTransform;
    }

    //-----------------------------------------PUBLIC------------------------------------------//
    void Object::update() //Overriden by children
    {
        if(!m_enabled)
        {
            return;
        }
    }

    Model *Object::getModel()
    {
        return m_pModel;
    }

    Transform *Object::getTransform()
    {
        return m_pTransform;
    }

    int Object::getId()
    {
        return m_id;
    }

    void Object::setEnabled(bool flag)
    {
        m_enabled = flag;
    }

    bool Object::isEnabled()
    {
        return m_enabled;
    }
    
    //-----------------------------------------PRIVATE------------------------------------------//
    void Object::onUpdateMaterialEvent(OnUpdateMaterialEvent event)
    {
        if(!m_enabled)
        {
            return;
        }

        for(int i = 0; i < m_pModel->getMeshNum(); i++)
        {
            Mesh *mesh = m_pModel->getMesh(i);
            glm::vec3 ambientColor = glm::vec3(event.materialAmbient[0],  event.materialAmbient[1], event.materialAmbient[2]);
            glm::vec3 diffuseColor = glm::vec3(event.materialDiffuse[0], event.materialDiffuse[1], event.materialDiffuse[2]);
            glm::vec3 specularColor = glm::vec3(event.materialSpecular[0], event.materialSpecular[1], event.materialSpecular[2]);
            
            for(int j = 1; j < mesh->getMaterialNum(); j++)
            {
                Material *mat = mesh->getMaterial(j);
                
                ambientColor.x = event.materialAmbient[0] * mat->ambient.x;
                ambientColor.y = event.materialAmbient[1] * mat->ambient.y;
                ambientColor.z = event.materialAmbient[2] * mat->ambient.z; //glm::vec3(event.materialAmbient[0],  event.materialAmbient[1], event.materialAmbient[2]);
                diffuseColor.x = event.materialDiffuse[0] * mat->diffuse.x;
                diffuseColor.y = event.materialDiffuse[1] * mat->diffuse.y;
                diffuseColor.z = event.materialDiffuse[2] * mat->diffuse.z;//glm::vec3(event.materialDiffuse[0], event.materialDiffuse[1], event.materialDiffuse[2]);
                specularColor.x = event.materialSpecular[0] * mat->specular.x;
                specularColor.y = event.materialSpecular[1] * mat->specular.y;
                specularColor.z = event.materialSpecular[2] * mat->specular.z; //glm::vec3(event.materialSpecular[0], event.materialSpecular[1], event.materialSpecular[2]);
            }

            Material *mainMat = mesh->getMaterial(0);
            
            mainMat->ambient = ambientColor;
            mainMat->diffuse = diffuseColor;
            mainMat->specular = specularColor;
            mainMat->shininess = event.materialShininess;
            mainMat->outlineThickness = event.outlineThickness;
        }
    }
   
    void Object::normalize(std::vector<Mesh*> meshes, Transform *transform)
    {
        float scaleValue = 1.0f;

        for(uint m = 0; m < meshes.size(); m++)
        {
            Mesh *mesh = meshes[m];

            for(int v = 0; v < mesh->getVertexNum()/3; v++)
            {
                float x = mesh->getVertex(v);
                float y = mesh->getVertex(v+1);
                float z = mesh->getVertex(v+2);

                if(x > scaleValue)
                    scaleValue = x;
                if(y > scaleValue)
                    scaleValue = y;
                if(z > scaleValue)
                    scaleValue = z;
            }
        }

        std::cout << "Scalevalue: " << scaleValue << std::endl;

        if(scaleValue > 0)
        {
            scaleValue = (1 / scaleValue)/2; 

            transform->scale(vec3(scaleValue, scaleValue, scaleValue));
        }
    }
}