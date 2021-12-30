#pragma once

#include "model.hpp"
#include "openglinput.hpp"
#include "transform.hpp"

namespace Umu
{
    class Object
    {
        public:
            Object(Model *model);
            ~Object();
            Model *getModel();
            Transform *getTransform();
            
        private:
            Model *m_pModel;
            Transform *m_pTransform;

            void normalize(std::vector<Mesh*> meshes, Transform *transform);
    };
}