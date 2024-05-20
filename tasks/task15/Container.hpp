#pragma once

#include <iostream>

template<typename... Types>
class Container {
public:
    Container(Types... args) { }
    
    template<typename T>
    T getElement(size_t idx) { }
};