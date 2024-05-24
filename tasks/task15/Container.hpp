#pragma once

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

        auto init_shift = [&]<typename T>(T&& arg) {
            shifts[counter++] = shift;
            shift += sizeof(T);
        };
        ((init_shift(args)), ...);
    }
    
    template<typename T>
    void free_mem(auto& counter) {
        (*((T*) ( memory + shifts[counter++]))).~T();
    }

    ~Container() {
        std::cout << "Container destructor was called" << std::endl;
        size_t counter = 0;
        ((free_mem<Types>(counter)), ...);
    }
    
    template<typename T>
    T& getElement(size_t idx) {
        return *((T*) (memory + shifts[idx]));   
    }
};