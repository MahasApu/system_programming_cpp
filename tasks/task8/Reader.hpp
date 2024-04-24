#pragma once

#include "IO.hpp"

class Reader : virtual public IO {
public:
    virtual ~Reader() { }
    virtual bool read(int& buf) = 0;
    virtual bool read(char& buf) = 0;
    virtual bool read(std::string& str) = 0;
};