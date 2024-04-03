#pragma once

#include <iostream>


// prohibited 
template<typename T>
class ScopedPointerProhibited {
    T* pointer;

public:
    ScopedPointerProhibited(T* raw): pointer(raw) { }
    ScopedPointerProhibited(const ScopedPointerProhibited& other) = delete;
    ScopedPointerProhibited(ScopedPointerProhibited&& other) {
        std::cout << "move constructor called" << std::endl;
        pointer = other.pointer;
        other.pointer = nullptr;
    }
    
    ScopedPointerProhibited& operator=(ScopedPointerProhibited other) {
        std::cout << "copy-and-swap operator called" << std::endl;
        if (this != &other) { std::swap(pointer, other.pointer); }
        return *this;
    }

    T& operator*() { return *pointer;}
    const T& operator*() const { return *pointer; }
    T* operator->() { return pointer; }
    const T* operator->() const { return pointer; }

    ~ScopedPointerProhibited() { delete pointer; }


    std::optional<T> get() { 
        if (!pointer) return std::nullopt;
        return {*pointer}; 
    }
        
    const std::optional<T> get() const { 
        if (!pointer) return std::nullopt;
        return {*pointer};
    }

};

