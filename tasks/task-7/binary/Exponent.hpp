#pragma once

#include "../Binary.hpp"

class Exponent: protected Binary {
public:
    Exponent(Expression* first, Expression* second):
            Binary(first, second) { }
    Expression* diff(std::string) override { return nullptr; };

};