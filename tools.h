#pragma once

#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include "assimp.hpp"
#include "mesh.hpp"

inline bool fileExists (const std::string& name) 
{
    struct stat buff;
    if(stat(name.c_str(), &buff) == 0)
    {
        return true;
    }
    else
    {
        return false;
    } 
}