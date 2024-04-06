#pragma once

#include <boost/lexical_cast.hpp>

#include "../Expression.hpp"

class Val: public Expression {
protected:
    int value;
public:
    Val(int value): value(value) { }

    Expression* diff(std::string var) override {
        return new Val(0);
    };

    std::string get_expr() override {
        return boost::lexical_cast<std::string>(value);
    }
};