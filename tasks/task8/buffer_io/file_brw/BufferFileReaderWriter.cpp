#include "BufferFileReaderWriter.hpp"

#include <cstdio>
#include <string>


bool BufferFileReaderWriter::upload_to_src() {
    if (!BufferWriter::opened || std::feof(file_)) return false;
    for(char c: BufferWriter::buffer) {
        std::fprintf(file_, "%c", c);
    }
    BufferWriter::buffer.clear();
    BufferWriter::pos = 0;
    return true;
}

bool BufferFileReaderWriter::upload_from_src() {
    if (!BufferReader::opened || std::feof(file_)) return false;
    BufferReader::buffer.clear();
    BufferReader::pos = 0;
    auto src_changed = [&](){ return pos_ != std::ftell(file_); };
    for(size_t i = 0; i < BufferReader::buffer_size; i++) {
        if (!src_changed()) upload_to_src();
        if (!src_changed()) break;

        char c;
        std::fseek(file_, pos_++, 0);
        if (!std::fscanf(file_, "%c", &c)) return false;
        BufferReader::buffer.push_back(c);
    }
    if (src_changed() && BufferReader::buffer.empty()) return false;
    return true;
}

bool BufferFileReaderWriter::is_open() const { return file_ != NULL; }
bool BufferFileReaderWriter::eof() const { return std::feof(file_); }
void BufferFileReaderWriter::close() {
    if (file_) {
        if (!upload_to_src()) throw "Unable to write data from buffer!";
        std::fclose(file_); 
        file_ = NULL;
        BufferReader::opened = false;
        BufferWriter::opened = false;
    }

}

bool BufferFileReaderWriter::read(std::string& src) {
    src.clear();
    char c;
    do { 
        if(!read(c)) break;
        src.push_back(c);
    } while (c);
    return true;
}

bool BufferFileReaderWriter::read(int& src) {
    char c;
    if (!read(c)) return false;
    src = c - '0';
    return true;
}

bool BufferFileReaderWriter::read(char& src) {
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

bool BufferFileReaderWriter::write(int& src) {
    std::string tmp = std::to_string(src);
    return write(tmp);
}

bool BufferFileReaderWriter::write(char& src) {
    BufferWriter::buffer.push_back(src);
    BufferWriter::pos++;
    if (BufferWriter::pos == BufferWriter::buffer_size) {
        if (!upload_to_src()){
            std::cout << "write_char: Unable to read data from buffer!" << std::endl;
            return false;
        }
    }
    return true;

}

bool BufferFileReaderWriter::write(std::string& src) {
    for(char& c: src) if(!write(c)) return false;
    return true;
}