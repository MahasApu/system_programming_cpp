#pragma once

#include "../Binary.hpp"

class Sub: protected Binary {
public:
    Sub(Expression* first, Expression* second):
            Binary(first, second) { }
    Expression* diff(std::string) override { return nullptr; };

};