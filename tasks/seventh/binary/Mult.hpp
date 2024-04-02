#pragma once

#include "../Binary.hpp"

class Mult: protected Binary {
public:
    Mult(Expression* first, Expression* second):
            Binary(first, second) { }
    Expression* diff(std::string) override { return nullptr; };

};