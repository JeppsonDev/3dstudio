#include "texture2d.hpp"
#include "image.hpp"
#include <vector>

namespace Umu
{
    Texture2D::Texture2D(std::string path)
    {
        m_show = false;
        m_hasdata = true;

        Image::flipYOnLoad();
        m_data = Image::load(path, &m_width, &m_height, &channels, 0);

        if(m_data)
        {
            GLenum format;

            switch(channels)
            {
                case 1: format = GL_LUMINANCE; break;
                case 2: format = GL_LUMINANCE_ALPHA; break;
                case 3: format = GL_RGB; break;
                case 4: format = GL_RGBA; break;
            }

            glGenTextures(1, &m_id);
            glBindTexture(GL_TEXTURE_2D, m_id);

            glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glBindTexture(GL_TEXTURE_2D, 0);
            Image::free(m_data);
        }
        else
        {
            std::cout << "Failed to load texture: " << path << std::endl;
            Image::free(m_data);
        }
    }

    Texture2D::Texture2D()
    {
        m_hasdata = false;
        m_show = false;
    }

    Texture2D::~Texture2D()
    {
        if(!m_hasdata)
        {
            return;
        }

        std::cout << "Freeing Texture2D" << std::endl;

        glDeleteTextures(1, &m_id);
    }

    //-----------------------------------------PUBLIC------------------------------------------//
    bool Texture2D::bind(unsigned int slot)
    {
        if(!m_hasdata)
        {
            return false;
        }

        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_id);

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