#pragma once

#include "../Binary.hpp"
#include "../unary/Val.hpp"
#include "Mult.hpp"


class Exponent: public Binary {
public:
    Exponent(Expression* first, Val* second):
            Binary(first, second, "^") { }
            
    Expression* diff(std::string) override {
        // looks bad :(
        Val* tmp = dynamic_cast<Val*>(second); 
        int tmp_val = std::stoi(tmp->get_expr());
        return new Mult(second,new Exponent(first, new Val(tmp_val - 1)));
     }

};