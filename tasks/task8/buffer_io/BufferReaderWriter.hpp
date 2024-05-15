#pragma once

#include <iostream>
#include <vector>

#include "../ReaderWriter.hpp"

class BufferReaderWriter: public ReaderWriter {

protected:
    bool opened;
    std::vector<char> buffer_write;
    std::vector<char> buffer_read;
    size_t buffer_size;

    BufferReaderWriter(size_t buffer_size):
                                opened(true),
                                buffer_size(buffer_size) { }

    virtual bool upload_to_src() = 0;
    virtual bool upload_from_src() = 0;
};