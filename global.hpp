/**
 * @file global.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 *
 * @brief A hack class required in order to not give the program a circular dependency between the scene and the openglwindow. 
          Highly temporary
 *
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include "observer.hpp"

namespace Umu
{
    /**
     * @brief Data for when window updates
     * 
     */
    struct OnUpdateWindowEvent
    {
        int width;
        int height;
    };

    class Global
    {
        public:
            static int window_width;
            static int window_height;
            static Observer<OnUpdateWindowEvent> *m_onUpdateWindowObserver;

            /**
             * @brief Get the On Update Window Observer object
             * 
             * @return Observer<OnUpdateWindowEvent>* 
             */
            static Observer<OnUpdateWindowEvent> *getOnUpdateWindowObserver();
    };
}