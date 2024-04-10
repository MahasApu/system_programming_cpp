#pragma once

#include "../Binary.hpp"

class Add: public Binary {
public:
    Add(Expression* _first, Expression* _second):
            Binary(_first, _second, "+") { }

    Add(const Add& other):
            Binary(other._first->clone(), other._second->clone(), "+") { }
            
    Expression* diff(std::string var) override {
        return new Add(_first->diff(var), _second->diff(var));
    }

    Expression* clone() override {
        return new Add(*this);
    }
};