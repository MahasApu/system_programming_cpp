#pragma once

#include "../Binary.hpp"
#include "Add.hpp"

class Mult: public Binary {
public:
    Mult(Expression* first, Expression* second):
            Binary(first, second, "*") { }
            
    Expression* diff(std::string var) override {
        return new Add(new Mult(first->diff(var), second), new Mult(first, second->diff(var)));
    }

};