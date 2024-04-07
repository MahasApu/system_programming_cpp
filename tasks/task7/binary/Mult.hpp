#pragma once

#include "../Binary.hpp"
#include "Add.hpp"

class Mult: public Binary {
public:
    Mult(Expression* _first, Expression* _second):
            Binary(_first, _second, "*") { }
            
    Expression* diff(std::string var) override {
        return new Add(new Mult(_first->diff(var), _second->get_copy()), new Mult(_first->get_copy(), _second->diff(var)));
    }

    Expression* get_copy() override {
        return new Mult(_first->get_copy(), _second->get_copy());
    }
};