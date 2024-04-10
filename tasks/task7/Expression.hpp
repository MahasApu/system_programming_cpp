#pragma once

#include <iostream>
#include <string>

class Expression {
protected:
public:
    Expression() { }
    virtual ~Expression() { }
    
    virtual Expression* diff(std::string var) = 0;
    virtual std::string symbolic() = 0;
    virtual Expression* clone() = 0;
};

