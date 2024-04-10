#pragma once

#include "../Binary.hpp"
#include "Add.hpp"

class Mult: public Binary {
public:
    Mult(Expression* _first, Expression* _second):
            Binary(_first, _second, "*") { }
            
    Mult(const Mult& other):
        Binary(other._first->clone(), other._second->clone(), "*") { }
            
    Expression* diff(std::string var) override {
        return new Add(new Mult(_first->diff(var), _second->clone()), new Mult(_first->clone(), _second->diff(var)));
    }

    Expression* clone() override {
        return new Mult(*this);
    }
};