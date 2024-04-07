#pragma once

#include "Expression.hpp"

class Binary: public Expression {
protected:
    Expression* first;
    Expression* second;
    std::string _operator;

public:
    Binary(Expression* first, Expression* second, std::string _operator):
                        first(first),
                        second(second), 
                        _operator(_operator) { }
    Binary(const Binary& other) = default;
    Binary& operator=(const Binary& other) = default;
    virtual ~Binary() {
        std::cout << "del in binary" << std::endl;
        delete first;
        delete second;
    }

    std::string get_symbolic() override {
         return first->get_symbolic()  + _operator + second->get_symbolic(); 
    }
};