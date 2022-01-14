/**
 * @file object.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 *
 * @brief 
 *
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "model.hpp"
#include "openglinput.hpp"
#include "transform.hpp"
#include "material.h"

namespace Umu
{
    class Object
    {
        public:
            /**
             * @brief Construct a new Object object
             * 
             * @param model 
             */
            Object(int id, Model *model);

            /**
             * @brief Destroy the Object object
             * 
             */
            virtual ~Object();

            /**
             * @brief Updates the object
             * 
             */
            virtual void update();

            /**
             * @brief Gets Material
             * 
             * @return Material 
             */
            Material getMaterial();

            /**
             * @brief Gets Model
             * 
             * @return Model* 
             */
            Model *getModel();

            /**
             * @brief Gets Id
             * 
             * @return int 
             */
            int getId();

            /**
             * @brief Gets Transform
             * 
             * @return Transform* 
             */
            Transform *getTransform();

            /**
             * @brief Sets Enabled
             * 
             * @param flag 
             */
            void setEnabled(bool flag);

            /**
             * @brief checks if object is enabled
             * 
             * @return true 
             * @return false 
             */
            bool isEnabled();
            
        protected:
            bool m_enabled;

        private:
            Model *m_pModel;
            Transform *m_pTransform;
            int m_id;
            
            /**
             * @brief On update the material event
             * 
             * @param event 
             */
            void onUpdateMaterialEvent(OnUpdateMaterialEvent event);

            /**
             * @brief Normalizes the meshes of the object to an NDC cube
             * 
             * @param meshes 
             * @param transform 
             */
            void normalize(std::vector<Mesh*> meshes, Transform *transform);
    };
}