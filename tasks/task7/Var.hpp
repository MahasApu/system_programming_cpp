#pragma once

#include "Val.hpp"

class Var: public Expression {
    std::string _variable;

public:
    Var(std::string var): _variable(var) { }
    Var(const Var& other): _variable(other._variable) { }

    ~Var() { std::cout << "del var" << std::endl; }

    Expression* diff(std::string var) override {
        if (this->_variable == var) {
            return new Val(1);
        }
        return new Val(0);
    };

    std::string symbolic() override {
        return _variable;
    }

    Expression* clone() override {
        return new Var(*this);
    }
};