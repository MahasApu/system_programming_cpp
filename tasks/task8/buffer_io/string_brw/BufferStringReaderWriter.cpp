#include "BufferStringReaderWriter.hpp"

#include <cstdio>
#include <string>


bool BufferStringReaderWriter::upload_to_src() {
    if (!opened) return false;
    for(char c: BufferWriter::buffer) {
        str_.push_back(c);
    }
    BufferWriter::buffer.clear();
    BufferWriter::pos = 0;
    return true;
}

bool BufferStringReaderWriter::upload_from_src() {
    if (!opened) return false;
    BufferReader::buffer.clear();
    BufferReader::pos = 0;
    auto src_changed = [&pos_ = pos_, &str_ = str_](){ return pos_ != str_.size(); };
    for(size_t i = 0; i < BufferReader::buffer_size; i++) {
        if (!src_changed()) upload_to_src(); // load data from write buffer
        if (!src_changed()) break ;          // if nothing happend - break
        BufferReader::buffer.push_back(str_.at(pos_++));
    }
    if (src_changed() && BufferReader::buffer.empty()) { return false;}
    return true;
}

bool BufferStringReaderWriter::is_open() const { return opened; }
bool BufferStringReaderWriter::eof() const { return false; }
void BufferStringReaderWriter::close() {
    if (opened) {
        if (!upload_to_src()) {
            std::cout << "close: Unable to write data from buffer!" << std::endl;
            return;}
        opened = false;
    }
}

bool BufferStringReaderWriter::read(char& src) {
    if (BufferReader::pos == BufferReader::buffer.size()) {
        if (!upload_from_src()) {
            std::cout << "read_char : Unable to write data from src!" << std::endl;
            return false;
        }
    }

    if (BufferReader::pos != BufferReader::buffer.size()) {
        src = BufferReader::buffer.at(BufferReader::pos++);
        return true;
    }
    return false;
}

bool BufferStringReaderWriter::read(int& src) {
    char c;
    if (!read(c)) return false;
    src = c - '0';
    return true;
}

bool BufferStringReaderWriter::read(std::string& src) {
    src.clear();
    char c;
    do { 
        if(!read(c)) break;
        src.push_back(c);
    } while (c);
    return true;
}


bool BufferStringReaderWriter::write(int& src) {
    std::string tmp = std::to_string(src);
    return write(tmp);
}

bool BufferStringReaderWriter::write(char& src) {
    BufferWriter::buffer.push_back(src);
    BufferWriter::pos++;
    if (BufferWriter::pos == BufferWriter::buffer_size) {
        if (!upload_to_src()) { 
            std::cout << "write_char: Unable to read data from buffer!" << std::endl;
            return false;
        }
    }
    return true;
}

bool BufferStringReaderWriter::write(std::string& src) {
    for(char& c: src) if(!write(c)) return false;
    return true;
}