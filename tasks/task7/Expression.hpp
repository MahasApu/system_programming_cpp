#pragma once

#include <iostream>
#include <string>


class Expression {
    
public:
    Expression() {};
    Expression(const Expression& other) = default;
    Expression& operator=(const Expression& other) = default;

    virtual ~Expression() { };
    virtual Expression* diff(std::string var) = 0;
    virtual std::string get_expr() = 0;
};

