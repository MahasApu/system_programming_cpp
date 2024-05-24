#pragma once 

#include "../Buffer.hpp"
#include "../Reader.hpp"

class BufferReader: public Buffer, public Reader {
public:
    BufferReader(size_t size): Buffer(size) { opened = true; }
    virtual bool upload_from_src() = 0;
};