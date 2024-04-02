#pragma once 

#include "Expression.hpp"

template <typename T>
class Unary: public Expression {
protected:
    T value;

public:
    Unary(T value) :
            value(value) { };
    ~Unary() = default;
};