#pragma once

#include "../Unary.hpp"
#include "Val.hpp"

class Var: public Unary<std::string> {
public:
    Var(std::string var): Unary(var) { }
    
    Expression* diff(std::string var) override {
        if (value == var) {
            return new Val(1);
        }
        return new Val(0);
    };
};