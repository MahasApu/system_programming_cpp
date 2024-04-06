#pragma once

#include "../Unary.hpp"

class Val: public Unary<int> {
public:
    Val(int value): Unary<int>(value) { }
    
    Expression* diff(std::string var) override {
        return new Val(0);
    };
};