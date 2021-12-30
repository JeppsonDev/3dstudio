#include "render3d.hpp"

namespace Umu
{
    Render3D::Render3D(void)
    {
        glEnable(GL_DEPTH_TEST);
    }

    Render3D::~Render3D(void)
    {
    }

    //-----------------------------------------PUBLIC------------------------------------------//
    void Render3D::render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    void Render3D::renderObject(Object *object)
    {
        Model *model = object->getModel();
        Shader *shader = model->getShader();

        shader->start();
        shader->setMat4("u_Model", object->getTransform()->getMatrix());

        for(int i = 0; i < model->getMeshNum(); i++)
        {
            Mesh *mesh = model->getMesh(i);

            mesh->bindVAO();
            mesh->render();
            mesh->unbindVAO();
            
        }
        shader->stop();
    }

    //-----------------------------------------PRIVATE------------------------------------------//
}