#pragma once

#include <iostream>
#include <malloc.h>

#include "../task14/TinyAllocator.hpp"

struct Point {
    int x, y;
    Point(int x_, int y_): x(x_), y(y_) { }
    Point(const Point& other): x(other.x), y(other.y) { };
    Point& operator=(const Point& other) {
        x = other.x;
        y = other.y;
        return *this;
    };

    friend std::ostream& operator<<(std::ostream& o, const Point& other) {
        o << other.x;
        o << " ";
        return o;
    }
    
    ~Point() {};
};


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