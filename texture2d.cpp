#include "texture2d.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

namespace Umu
{
    Texture2D::Texture2D(std::string path)
    {
        m_show = true;
        m_hasdata = true;

        stbi_set_flip_vertically_on_load(1);
        m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);

        if(m_LocalBuffer)
        {
            GLenum format;
            if (m_BPP == 1)
            {
                format = GL_RED;
            }   
            else if (m_BPP == 3)
            {
                format = GL_RGB;
            }
            else if (m_BPP == 4)
            {
                format = GL_RGBA;
            }   

            glGenTextures(1, &m_RendererId);
            glBindTexture(GL_TEXTURE_2D, m_RendererId);

            glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_LocalBuffer);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glBindTexture(GL_TEXTURE_2D, 0);
            stbi_image_free(m_LocalBuffer);
        }
        else
        {
            std::cout << "Failed to load texture: " << path << std::endl;
            stbi_image_free(m_LocalBuffer);
        }
    }

    Texture2D::Texture2D()
    {
        m_hasdata = false;
        m_show = false;
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &m_RendererId);
    }

    bool Texture2D::bind(unsigned int slot)
    {
        if(!m_hasdata)
        {
            return false;
        }

        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererId);
        return true;
    }

    void Texture2D::unbind()
    {
        if(!m_hasdata)
        {
            return;
        }
        
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture2D::show()
    {
        m_show = true;
    }

    void Texture2D::hide()
    {
        m_show = false;
    }
    
    bool Texture2D::shouldShow()
    {
        return m_show;
    }
}