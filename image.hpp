/**
 * @file image.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 *
 * @brief The class implementing stb_image.h
 *
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <string>

namespace Umu
{
    class Image
    {
        public:
            /**
             * @brief Loads an image
             * 
             * @param path 
             * @param width 
             * @param height 
             * @param nrChannels 
             * @param requiredComponents 
             * @return unsigned* 
             */
            static unsigned char* load(std::string path, int *width, int *height, int *nrChannels, int requiredComponents=0);

            /**
             * @brief Flips the image on Y on load
             * 
             */
            static void flipYOnLoad();

            /**
             * @brief Free an image
             * 
             * @param buffer 
             */
            static void free(unsigned char *buffer);
    };
}