#include "render3d.hpp"

namespace Umu
{
    Render3D::Render3D(void)
    {
        glEnable(GL_DEPTH_TEST);

        m_pMainShader = new TeddyShader("vshader.glsl", "fshader.glsl");
    }

    Render3D::~Render3D(void)
    {

    }

    //-----------------------------------------PUBLIC------------------------------------------//

    void Render3D::prepare(std::vector<float> vertices, std::vector<unsigned int> indices)
    {
        m_pMainMesh = new Mesh(vertices, indices);
        m_pMainMesh->prepareForRender(m_pMainShader);
    }

    void Render3D::render()
    {
        m_pMainShader->start();
        m_pMainShader->bindVAO();

        //TODO: Don't call OpenGL from Render3D
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        m_pMainMesh->render();
        m_pMainShader->pushTranslationMatrix(m_pMainMesh->getTransformationMatrix());

        m_pMainShader->unbindVAO();
        m_pMainShader->stop();
    }
}