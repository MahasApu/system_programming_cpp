#pragma once

#include "BufferReader.hpp"
#include "BufferWriter.hpp"

class BufferReaderWriter: public BufferReader, public BufferWriter {
public:
    BufferReaderWriter(size_t buffer_size): BufferReader(buffer_size),
                                            BufferWriter(buffer_size) { }
};