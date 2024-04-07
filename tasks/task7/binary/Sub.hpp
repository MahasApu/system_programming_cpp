#pragma once

#include "../Binary.hpp"

class Sub: public Binary {
public:
    Sub(Expression* _first, Expression* _second):
            Binary(_first, _second, "-") { }
            
    Expression* diff(std::string var) override {
        return new Sub(_first->diff(var), _second->diff(var));
    }

    Expression* get_copy() override {
        return new Sub(_first->get_copy(), _second->get_copy());
    }

};