#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>
#include <vector>

    template <class TData>
    struct Listener
    {
        std::function<void(TData)> listener;
    };

    template <class TData>
    class Observer
    {
        public:
            void invokeEvents(TData data)
            {
                for(unsigned int i = 0; i < listeners.size(); i++)
                {
                    listeners[i].listener(data);
                }  
            }

            void registerEvent(auto implementation)
            {
                Listener<TData> l;
                l.listener = implementation;

                listeners.push_back(l);
            }

            //TODO: Go around and clear events when the objects break... Also add an ID system so that individual events can
            //be removed
            void clearEvents()
            {
                listeners.clear();
            }

            std::vector<Listener<TData>> listeners;            
        private:
    };