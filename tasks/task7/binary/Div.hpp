#pragma once

#include <iostream>

#include "../Binary.hpp"
#include "Mult.hpp"
#include "Sub.hpp"

class Div: public Binary {
public:
    Div(Expression* _first, Expression* _second):
            Binary(_first, _second, "/") { }
    
    Div(const Div& other):
            Binary(other._first->clone(), other._second->clone(), "/") { }

    Expression* diff(std::string var) override { 
        return new Div(new Sub(
                        new Mult(_first->diff(var), _second->clone()),
                        new Mult(_first->clone(), _second->diff(var))),
                        new Mult(_second->clone(), _second->clone()));
    }
    
    std::string symbolic() override {
        return "(" + _first->symbolic() + ")" + _operator + "(" + _second->symbolic() + ")";
    }

    Expression* clone() override {
        return new Div(*this);
    }

};