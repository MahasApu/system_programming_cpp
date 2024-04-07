#pragma once

#include "../Binary.hpp"
#include "Mult.hpp"
#include "Sub.hpp"
#include "Exponent.hpp"
#include "../unary/Val.hpp"

class Div: public Binary {
public:
    Div(Expression* first, Expression* second):
            Binary(first, second, "/") { }

    Expression* diff(std::string var) override { 
        return new Div(new Sub(
                        new Mult(first->diff(var), second->get_copy()),
                        new Mult(first->get_copy(), second->diff(var))),
                        new Mult(second->get_copy(), second->get_copy()));
    }
    
    std::string get_symbolic() override {
        return "(" + first->get_symbolic() + ")" + _operator + "(" + second->get_symbolic() + ")";
    }

    Expression* get_copy() override {
        return new Div(first->get_copy(), second->get_copy());
    }

};