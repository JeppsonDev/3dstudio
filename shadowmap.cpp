#include "shadowmap.hpp"

#include "global.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Umu
{
    ShadowMap::ShadowMap()
    {
        init();
    }

    //-----------------------------------------PUBLIC------------------------------------------//
    glm::mat4 ShadowMap::calculateLightSpace(glm::vec3 lightPosition)
    {
        glm::mat4 lightProjection;
        glm::mat4 lightView;
        glm::mat4 lightSpaceMatrix;

        float near_plane = 1.0f;
        float far_plane = 50.5f;

        lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        lightView = glm::lookAt(lightPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.000001, 1.0, 0.000001));
        lightSpaceMatrix = lightProjection * lightView;

        return lightSpaceMatrix;
    }
    
    void ShadowMap::prepare()
    {
        glViewport(0, 0, 1024, 1024);
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void ShadowMap::unprepare()
    {
        glViewport(0, 0, Global::window_width, Global::window_height);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void ShadowMap::bind(int i)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, m_depthMapTextureId);
    }

    void ShadowMap::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    //-----------------------------------------PRIVATE------------------------------------------//
    void ShadowMap::init()
    {
        glGenFramebuffers(1, &m_fbo);
        
        glGenTextures(1, &m_depthMapTextureId);
        glBindTexture(GL_TEXTURE_2D, m_depthMapTextureId);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   

        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMapTextureId, 0);
        
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);  
    }
}