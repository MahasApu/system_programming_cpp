#pragma once

#include "Reader.hpp"
#include "Writer.hpp"

class ReaderWriter: public Reader, public Writer { 
protected:
    size_t pos_ = 0;
public:
    virtual ~ReaderWriter() { }
};