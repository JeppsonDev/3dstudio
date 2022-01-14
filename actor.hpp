/**
 * @file actor.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 *
 * @brief A scene actor, which is an object that can move around through arrow keys
 *
 * @version 0.1
 * @date 2022-01-12
 * 
 */

#pragma once

#include "object.hpp"

namespace Umu
{
    class Actor : public Object
    {
        public:
            /**
            * @brief Construct a new Actor object
            * 
            * @param model 
            */
            Actor(int id, Model *model);

            /**
             * @brief Updates the actor
             * 
             */
            virtual void update() override;

        private:
            bool t;
            bool r;
            bool s;
    };
}