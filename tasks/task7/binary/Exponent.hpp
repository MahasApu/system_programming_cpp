#pragma once

#include "../Unary.hpp"
#include "Mult.hpp"


class Exponent: public Unary {
public:
    Exponent(Expression* expr):
            Unary(expr, "e^") { }

    Expression* diff(std::string var) override {
        return new Mult(expr->diff(var), this);
     }

    std::string get_expr() override {
         return _operator + expr->get_expr();
    }

};