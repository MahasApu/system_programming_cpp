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
        return new Div(new Sub(new Mult(first->diff(var), second), new Mult(first, second->diff(var))), new Mult(second, second));
    }
    
    std::string get_expr() override {
        return "(" + first->get_expr() + ")" + _operator + "(" + second->get_expr() + ")";
    }

};