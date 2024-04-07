#pragma once

#include "../Binary.hpp"

class Add: public Binary {
public:
    Add(Expression* _first, Expression* _second):
            Binary(_first, _second, "+") { }
            
    Expression* diff(std::string var) override {
        return new Add(_first->diff(var), _second->diff(var));
    }

    Expression* get_copy() override {
        return new Add(_first->get_copy(), _second->get_copy());
    }
};