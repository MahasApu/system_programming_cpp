#pragma once 

#include <string>

#include "Expression.hpp"

class Unary: public Expression {
protected:
    Expression* expr;
    std::string _operator;

public:
    Unary(Expression* expr, std::string _operator):
                                 expr(expr),
                                 _operator(_operator) { }
    Unary(const Unary& other) = default;
    Unary& operator=(const Unary& other) = default;
    ~Unary() { std::cout << "del in unary" << std::endl; }

};