#pragma once

#include <iostream>

#include "../task14/TinyAllocator.hpp"


template<typename... Types>
class Container {
    size_t shifts[sizeof...(Types)];
    char memory[get_size<Types...>];

public:
    Container(Types&&... args) { 
        allocate<get_size<Types...>>(memory, args...);
        size_t shift = 0;
        size_t counter = 0;

        auto init_shift = [&]<typename T>(T arg) {
            shifts[counter++] = shift;
            shift += sizeof(T);
        };

        ((init_shift(args)), ...);
    }

    ~Container() {}
    
    template<typename T>
    T getElement(size_t idx) {
        return *((T*) (memory + shifts[idx]));   
    }
};