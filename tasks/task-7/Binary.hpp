#pragma once

#include "Expression.hpp"

class Binary: public Expression {
protected:
    Expression* first;
    Expression* second;

public:
    Binary(Expression* first, Expression* second):
                        first(first),
                        second(second) { }
    ~Binary() {
        delete first;
        delete second;
    }
};