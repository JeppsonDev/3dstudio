#include "image.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

namespace Umu
{
    unsigned char* Image::load(std::string path, int *width, int *height, int *nrChannels, int requiredComponents)
    {
        return stbi_load(path.c_str(), width, height, nrChannels, STBI_rgb);
    }

    void Image::flipYOnLoad()
    {
        stbi_set_flip_vertically_on_load(1);
    }

    void Image::free(unsigned char* buffer)
    {
        stbi_image_free(buffer);
    }
}