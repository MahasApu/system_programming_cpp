#pragma once

#include "../Binary.hpp"
#include "Mult.hpp"
#include "Sub.hpp"
#include "Exponent.hpp"
#include "../unary/Val.hpp"

class Div: public Binary {
public:
    Div(Expression* _first, Expression* _second):
            Binary(_first, _second, "/") { }

    Expression* diff(std::string var) override { 
        return new Div(new Sub(
                        new Mult(_first->diff(var), _second->get_copy()),
                        new Mult(_first->get_copy(), _second->diff(var))),
                        new Mult(_second->get_copy(), _second->get_copy()));
    }
    
    std::string get_symbolic() override {
        return "(" + _first->get_symbolic() + ")" + _operator + "(" + _second->get_symbolic() + ")";
    }

    Expression* get_copy() override {
        return new Div(_first->get_copy(), _second->get_copy());
    }

};