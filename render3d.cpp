#include "render3d.hpp"

namespace Umu
{
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMap;
    unsigned int depthMapFBO;

    unsigned int planeVBO;
    unsigned int planeVAO;

    Render3D::Render3D(void)
    {
        glEnable(GL_DEPTH_TEST);
        
        //shadow mapping
        glGenFramebuffers(1, &depthMapFBO);

        //Generate depth map
        glGenTextures(1, &depthMap);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // attach depth texture as FBO's depth buffer
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);   






                float planeVertices[] = {
            // positions            // normals         // texcoords
            25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
            -25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
            -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

            25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
            -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
            25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
        };
        // plane VAO
        glGenVertexArrays(1, &planeVAO);
        glGenBuffers(1, &planeVBO);
        glBindVertexArray(planeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindVertexArray(0);    
    }

    Render3D::~Render3D(void)
    {
    }

    //-----------------------------------------PUBLIC------------------------------------------//
    void Render3D::render()
    {
    }

    void Render3D::bindDepthMap()
    {
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);   
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Render3D::unbindDepthMap()
    {
        //Prepare for normal rendering
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //TODO: Don't hardcode screen w&h
        glViewport(0, 0, 960.0f, 540.0f);
        glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    int Render3D::getDepthMap()
    {
        return depthMap;
    }

    void Render3D::useShader(Shader *shader)
    {
        m_pShader = shader;
    }

    void Render3D::renderObject(Object *object, bool shadowflag)
    {
        Model *model = object->getModel();
        Shader *shader = m_pShader;

        shader->start();

        bool didBind = model->getTexture()->bind(0);

        //Set and bind texture
        if(shadowflag)
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, getDepthMap());            
        }  

        // floor
        shader->setMat4("u_Model", glm::mat4(1.0f));
        glBindVertexArray(planeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);   
        glBindVertexArray(0);   

        if(didBind)
        {
            shader->setInt("u_ShouldRenderTexture", model->getTexture()->shouldShow());
        }             

        //TODO: Only set mat4 when transform change
        shader->setMat4("u_Model", object->getTransform()->getMatrix());

        for(int i = 0; i < model->getMeshNum(); i++)
        {
            Mesh *mesh = model->getMesh(i);

            mesh->bindVAO();
            mesh->render();
            mesh->unbindVAO();
        }

        //Unbind
        if(didBind)
        {
            model->getTexture()->unbind();
            shader->setInt("u_ShouldRenderTexture", 0);
        }  

        shader->stop();
    }

    //-----------------------------------------PRIVATE------------------------------------------//
}