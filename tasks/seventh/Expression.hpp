#pragma once

#include <string>


class Expression {
public:
    virtual ~Expression() { };
    virtual Expression* diff(std::string var) = 0;
};