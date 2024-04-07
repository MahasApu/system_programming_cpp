#pragma once

#include <boost/lexical_cast.hpp>

#include "../Expression.hpp"

class Val: public Expression {
protected:
    int value;

public:
    Val(int value): value(value) { }
    Val(const Val& other) = default;
    Val& operator=(const Val& other) = default;
    ~Val() { std::cout << "del val" << std::endl;}

    Expression* diff(std::string var) override {
        return new Val(0);
    };

    std::string get_symbolic() override {
        return boost::lexical_cast<std::string>(value);
    }

    Expression* get_copy() override {
        return new Val(value);
    }
};