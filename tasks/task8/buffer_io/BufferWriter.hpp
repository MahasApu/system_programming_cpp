#pragma once 

#include "../Buffer.hpp"
#include "../Writer.hpp"

class BufferWriter: public Buffer, public Writer {
public:
    BufferWriter(size_t size): Buffer(size) { opened = true; }
    virtual bool upload_to_src() = 0;
};