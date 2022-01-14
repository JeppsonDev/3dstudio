#include "global.hpp"

namespace Umu
{
    int Global::window_width;
    int Global::window_height;
    
    Observer<OnUpdateWindowEvent> *Global::m_onUpdateWindowObserver = new Observer<OnUpdateWindowEvent>();

    //-----------------------------------------PUBLIC------------------------------------------//
    Observer<OnUpdateWindowEvent> *Global::getOnUpdateWindowObserver()
    {
        return m_onUpdateWindowObserver;
    }
}