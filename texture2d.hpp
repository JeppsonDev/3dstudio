#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

namespace Umu
{
    //TODO: rewrite this class
    class Texture2D
    {
        private:
            unsigned int m_RendererId = 0;
            std::string m_FilePath = "";
            unsigned char* m_LocalBuffer = nullptr;
            int m_Width = 0;
            int m_Height = 0;
            int m_BPP = 0;

        public:
            Texture2D(std::string path);
            ~Texture2D();
            void bind(unsigned int slot);
            void unbind();
    };
}