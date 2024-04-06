#pragma once

#include "../Binary.hpp"

class Sub: public Binary {
public:
    Sub(Expression* first, Expression* second):
            Binary(first, second, "-") { }
            
    Expression* diff(std::string var) override {
        return new Sub(first->diff(var), second->diff(var));
     }
};