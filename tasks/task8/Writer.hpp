#pragma once

#include "IO.hpp"

class Writer : virtual public IO {
public:
    virtual ~Writer() { }
    virtual bool write(int& buf) = 0;
    virtual bool write(char& buf) = 0;
    virtual bool write(std::string& str) = 0;
};

