#pragma once

#include "../Binary.hpp"

class Div: protected Binary {
public:
    Div(Expression* first, Expression* second):
            Binary(first, second) { }
    Expression* diff(std::string) override { return nullptr; };

};