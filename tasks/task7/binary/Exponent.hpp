#pragma once

#include "../Unary.hpp"
#include "Mult.hpp"


class Exponent: public Unary {
public:
    Exponent(Expression* _expr):
            Unary(_expr, "e^") { }

    Expression* diff(std::string var) override {
        return new Mult(_expr->diff(var), this->get_copy());
     }

    std::string get_symbolic() override {
         return _operator + _expr->get_symbolic();
    }

    Expression* get_copy() override {
        return new Exponent(_expr->get_copy());
    }

};