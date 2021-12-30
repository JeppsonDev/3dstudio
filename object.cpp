#include "object.hpp"

namespace Umu
{
    Object::Object(Model *model)
    {
        m_pModel = model;
        m_pTransform = new Transform();

        normalize(model->getMeshes(), m_pTransform);
    }

    Object::~Object()
    {
        delete m_pModel;
    }

    //-----------------------------------------PUBLIC------------------------------------------//
    Model *Object::getModel()
    {
        return m_pModel;
    }

    Transform *Object::getTransform()
    {
        return m_pTransform;
    }
    
    //-----------------------------------------PRIVATE------------------------------------------//
    void Object::normalize(std::vector<Mesh*> meshes, Transform *transform)
    {
        float scaleValue = 0.0f;

        //TODO: Hardcoded to only work for triangles
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

        scaleValue = (1 / scaleValue)/2; 

        transform->scale(vec3(scaleValue, scaleValue, scaleValue));
    }
}