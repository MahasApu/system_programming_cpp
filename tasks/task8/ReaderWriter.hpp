#pragma once

#include "Reader.hpp"
#include "Writer.hpp"

class ReaderWriter: public Reader, public Writer { 
protected:
    size_t read_pos_ = 0;
    size_t write_pos_ = 0;

public:
    virtual ~ReaderWriter() { }
};