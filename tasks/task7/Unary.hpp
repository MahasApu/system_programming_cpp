#pragma once 

#include <boost/lexical_cast.hpp>
#include <string>

#include "Expression.hpp"

template <typename T>
class Unary: public Expression {
protected:
    const T value;
    
public:
    Unary(const T value): value(value) { }
    Unary(const Unary& other) = default;
    Unary& operator=(const Unary& other) = default;
    ~Unary() { std::cout << "del in unary" << std::endl; }

    std::string get_expr() override {
         return boost::lexical_cast<std::string>(value);
    }
};