/**
 * @file tools.h
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 * @brief General tools compatiable with C
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include "assimp.hpp"
#include "mesh.hpp"

/**
 * @brief Checks if a file exists
 * 
 * @param name 
 * @return true 
 * @return false 
 */
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