#pragma once

#include "../Unary.hpp"
#include "Val.hpp"

class Var: public Unary<const char*> {
public:
    Var(const char* var): 
            Unary<const char*>(var) { }
    ~Var() = default;

    Expression* diff(std::string var) override {
        if (value == var) {
            return new Val(1);
        }
        return nullptr;
    };
};