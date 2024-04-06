#pragma once

#include "Val.hpp"

class Var: public Expression {
    std::string var;

public:
    Var(std::string var): var(var) { }

    Expression* diff(std::string var) override {
        if (this->var == var) {
            return new Val(1);
        }
        return new Val(0);
    };

        std::string get_expr() override {
            return var;
    }
};