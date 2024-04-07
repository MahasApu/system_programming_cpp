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
    Binary(const Binary& other) = default;
    Binary& operator=(const Binary& other) = default;
    virtual ~Binary() {
        std::cout << "del in binary" << std::endl;
        delete _first;
        delete _second;
    }

    std::string get_symbolic() override {
         return _first->get_symbolic()  + _operator + _second->get_symbolic(); 
    }
};