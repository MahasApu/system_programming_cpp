#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../ReaderWriter.hpp"

class BufferReaderWriter: public ReaderWriter {

protected:
    bool opened;
    std::vector<char> buffer_write;
    std::vector<char> buffer_read;
    size_t buffer_size;
    bool buffer_r_end = false;
    bool buffer_w_end = false;

    BufferReaderWriter(size_t buffer_size):
                                opened(true),
                                buffer_size(buffer_size) { }

    virtual bool upload_to_src() = 0;
    virtual bool upload_from_src() = 0;
};