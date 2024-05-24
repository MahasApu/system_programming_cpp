#pragma once 

#include <iostream>
#include <vector>

class Buffer {
protected:
    std::vector<char> buffer;
    size_t buffer_size;
    size_t pos = 0;
public:
    Buffer(size_t size) : buffer_size(size) { }
    ~Buffer() { }
};