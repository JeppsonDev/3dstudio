#include "render3d.hpp"

namespace Umu
{
    Render3D::Render3D(void)
    {
        glEnable(GL_DEPTH_TEST);
    }

    Render3D::~Render3D(void)
    {
        std::cout << "Freeing Render3D" << std::endl;
    }

    //-----------------------------------------PUBLIC------------------------------------------//
    void Render3D::render()
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Render3D::renderObject(Object *object, Shader *shader, ShadowMap *shadowmap)
    {
        Model *model = object->getModel();
        
        shader->start();

        //Set and bind texture
        bool didBind = model->getTexture()->bind(0);

        if(didBind)
        {
            shader->setInt("u_Texture", 0);
            shader->setInt("u_ShouldRenderTexture", model->getTexture()->shouldShow());
        }

        shadowmap->bind(1);
        shader->setInt("u_DepthTexture", 1);

        shader->setMat4("u_Model", object->getTransform()->getMatrix());

        for(int i = 0; i < model->getMeshNum(); i++)
        {
            Mesh *mesh = model->getMesh(i);

            mesh->bindVAO();

            shader->setVec3("u_AmbientConstant", mesh->getMaterial(0)->ambient);
            shader->setVec3("u_DiffuseConstant", mesh->getMaterial(0)->diffuse);
            shader->setVec3("u_SpecularConstant", mesh->getMaterial(0)->specular);
            shader->setFloat("u_Shininess", mesh->getMaterial(0)->shininess);
            shader->setFloat("u_OutlineThickness", mesh->getMaterial(0)->outlineThickness);
            //std::cout << "Outline thickness: " << mainMat->outlineThickness << std::endl;

            mesh->render();
            mesh->unbindVAO();
        }

        //Unbind
        if(didBind)
        {
            model->getTexture()->unbind();
            shader->setInt("u_ShouldRenderTexture", 0);
        }

        shadowmap->unbind();

        shader->stop();
    }

    //-----------------------------------------PRIVATE------------------------------------------//
}