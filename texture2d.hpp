/**
 * @file texture2d.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 *
 * @brief A 2D texture that can be loaded from file 
 *
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

namespace Umu
{
    class Texture2D
    {
        private:
            unsigned int m_id = 0;
            unsigned char* m_data = nullptr;
            int m_width = 0;
            int m_height = 0;
            int channels = 0;
            bool m_hasdata = false;
            bool m_show = true;

        public:
            /**
             * @brief Construct a new Texture 2 D object from file
             * 
             * @param path 
             */
            Texture2D(std::string path);

            /**
             * @brief Construct a new Texture 2 D object
             * 
             */
            Texture2D();

            /**
             * @brief Destroy the Texture 2 D object
             * 
             */
            ~Texture2D();

            /**
             * @brief Binds the texture to a texture slot
             * 
             * @param slot 
             * @return true 
             * @return false 
             */
            bool bind(unsigned int slot);

            /**
             * @brief Unbinds the texture (binds to 0)
             * 
             */
            void unbind();

            /**
             * @brief Shows the texture
             * 
             */
            void show();

            /**
             * @brief Hides the texture
             * 
             */
            void hide();

            /**
             * @brief returns true if a texture should show
             * 
             * @return true 
             * @return false 
             */
            bool shouldShow();
    };
}