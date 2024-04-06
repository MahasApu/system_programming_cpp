#pragma once

#include "../Binary.hpp"

class Add: public Binary {
public:
    Add(Expression* first, Expression* second):
            Binary(first, second, "+") { }
            
    Expression* diff(std::string var) override {
        return new Add(first->diff(var), second->diff(var));
    }
};