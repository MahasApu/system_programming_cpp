#pragma once

#include <iostream>

#include "Expression.hpp"


class ScopedExpression {
    Expression* pointer;

public:
    ScopedExpression(Expression* raw): pointer(raw) { }
    ScopedExpression(const ScopedExpression& other) = delete;

    ScopedExpression(ScopedExpression&& other) {
        std::cout << "move constructor called" << std::endl;
        pointer = other.pointer;
        other.pointer = nullptr;
    }

    ScopedExpression& operator=(ScopedExpression other) {
        std::cout << "copy-and-swap operator called" << std::endl;
        std::swap(pointer, other.pointer); 
        return *this;
    }

    Expression& operator*() { return *pointer;}
    const Expression& operator*() const { return *pointer; }
    Expression* operator->() { return pointer; }
    const Expression* operator->() const { return pointer; }

    ~ScopedExpression() { delete pointer; }

};