#pragma once

#include "../Binary.hpp"

class Sub: public Binary {
public:
    Sub(Expression* _first, Expression* _second):
            Binary(_first, _second, "-") { }

    Sub(const Sub& other):
        Binary(other._first->clone(), other._second->clone(), "-") { }
            
    Expression* diff(std::string var) override {
        return new Sub(_first->diff(var), _second->diff(var));
    }

    Expression* clone() override {
        return new Sub(*this);
    }

};