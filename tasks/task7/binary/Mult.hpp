#pragma once

#include "../Binary.hpp"
#include "Add.hpp"

class Mult: public Binary {
public:
    Mult(Expression* first, Expression* second):
            Binary(first, second, "*") { }
            
    Expression* diff(std::string var) override {
        return new Add(new Mult(first->diff(var), second->get_copy()), new Mult(first->get_copy(), second->diff(var)));
    }

    Expression* get_copy() override {
        return new Mult(first->get_copy(), second->get_copy());
    }
};