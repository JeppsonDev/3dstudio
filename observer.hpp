/**
 * @file observer.hpp
 * @author Jesper Byström (dv19jbm@cs.umu.se)
 *
 * @brief The class representing an observer in the observer/listener pattern. 
          Holds a list of litseners and invokes them appropiately
 *
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>
#include <vector>

    /**
     * @brief The data for a listener
     * 
     * @tparam TData 
     */
    template <class TData>
    struct Listener
    {
        std::function<void(TData)> listener;
    };

    template <class TData>
    class Observer
    {
        public:
            /**
             * @brief Invoke all listeners
             * 
             * @param data 
             */
            void invokeEvents(TData data)
            {
                for(unsigned int i = 0; i < listeners.size(); i++)
                {
                    listeners[i].listener(data);
                }  
            }

            /**
             * @brief Register an listener
             * 
             * @param implementation 
             */
            void registerEvent(auto implementation)
            {
                Listener<TData> l;
                l.listener = implementation;

                listeners.push_back(l);
            }

            /**
             * @brief Clear listeners
             * 
             */
            void clearEvents()
            {
                listeners.clear();
            }

            std::vector<Listener<TData>> listeners;            
        private:
    };