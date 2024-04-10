#pragma once

#include <boost/lexical_cast.hpp>

#include "../Expression.hpp"

class Val: public Expression {
    int _value;

public:
    Val(int _value): _value(_value) { }
    Val(const Val& other): _value(other._value) { }

    ~Val() { std::cout << "del val" << std::endl;}

    Expression* diff(std::string var) override {
        return new Val(0);
    };

    std::string symbolic() override {
        return boost::lexical_cast<std::string>(_value);
    }

    Expression* clone() override {
        return new Val(*this);
    }
};