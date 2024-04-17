#pragma once

#include "../Unary.hpp"
#include "../binary/Mult.hpp"


class Exponent: public Unary {
public:
    Exponent(Expression* _expr):
            Unary(_expr, "e^") { }

    Exponent(const Exponent& other) :
            Unary(other._expr->clone(), "e^") { }

    Expression* diff(std::string var) override {
        return new Mult(_expr->diff(var), this->clone());
     }

    Expression* clone() override {
        return new Exponent(*this);
    }

};