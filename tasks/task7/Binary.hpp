#pragma once

#include "Expression.hpp"

class Binary: public Expression {
protected:
    Expression* _first;
    Expression* _second;
    std::string _operator;

public:
    Binary(Expression* _first, Expression* _second, std::string _operator):
                        _first(_first),
                        _second(_second), 
                        _operator(_operator) { }

    virtual ~Binary() {
        std::cout << "del in binary" << std::endl;
        delete _first;
        delete _second;
    }

    std::string symbolic() override {
         return _first->symbolic()  + _operator + _second->symbolic(); 
    }
};