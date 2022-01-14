#pragma once

#include "object.hpp"

namespace Umu
{
    class Actor : public Object
    {
        public:
            Actor(Model *model);
            virtual void update() override;

        private:
            bool t;
            bool r;
            bool s;
    };
}