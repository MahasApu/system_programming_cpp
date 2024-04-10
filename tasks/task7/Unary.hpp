#pragma once 

#include <string>

#include "Expression.hpp"

class Unary: public Expression {
protected:
    Expression* _expr;
    std::string _operator;

public:
    Unary(Expression* _expr, std::string _operator):
                                 _expr(_expr),
                                 _operator(_operator) { }
    ~Unary() { 
        std::cout << "del in unary" << std::endl; 
        delete _expr;
    }

    std::string symbolic() override {
        return _operator + _expr->symbolic(); 
    }
};