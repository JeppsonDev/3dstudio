/**
 * @file render3d.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 *
 * @brief The class representing a 3D renderer
 *
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
#include <vector>
#include <string>
#include <stdint.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "assimp.hpp"
#include "object.hpp"
#include "shadowmap.hpp"

namespace Umu 
{
    class Render3D
    {
        public:
            /**
             * @brief Construct a new Render 3 D object
             * 
             */
            Render3D(void);

            /**
             * @brief Destroy the Render 3 D object
             * 
             */
            ~Render3D(void);

            /**
             * @brief Runs the renderer
             * 
             */
            void render();

            /**
             * @brief Renders an object
             * 
             * @param object 
             * @param shader 
             * @param shadowmap 
             */
            void renderObject(Object *object, Shader *shader, ShadowMap *shadowmap);
    };
}