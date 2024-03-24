#pragma once

#include <iostream>

// deep coping
template<typename T>
class ScopedPointerDeepCopy {
    T* pointer;

public:
    ScopedPointerDeepCopy(T* raw): pointer(raw) { }
    ScopedPointerDeepCopy(const ScopedPointerDeepCopy& other) {
        std::cout << "copy constructor called" << std::endl;
        pointer = new T(*other.pointer);
    }

    ScopedPointerDeepCopy(ScopedPointerDeepCopy&& other) {
        std::cout << "move constructor called" << std::endl;
        pointer = other.pointer;
        other.pointer = nullptr;
    }

    ScopedPointerDeepCopy& operator=(ScopedPointerDeepCopy other) {
        std::cout << "copy-and-swap operator called" << std::endl;
        if (this != &other) { std::swap(pointer, other.pointer); }
        return *this;
    }

    T& operator*() { return *pointer;}
    const T& operator*() const { return *pointer; }
    T* operator->() { return pointer; }
    const T* operator->() const { return pointer; }

    ~ScopedPointerDeepCopy() { delete pointer; }


    std::optional<T> get() { 
        if (!pointer) return std::nullopt;
        return {*pointer}; 
    }
        
    const std::optional<T> get() const { 
        if (!pointer) return std::nullopt;
        return {*pointer};
    }
};