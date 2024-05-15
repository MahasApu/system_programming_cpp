#include "BufferFileReaderWriter.hpp"

#include <cstdio>
#include <string>


bool BufferFileReaderWriter::upload_to_src() {
    if (!opened || std::feof(file_)) return false;
    std::fseek(file_, std::ftell(file_), 0);
    for(char c: buffer_write) {
        std::fprintf(file_, "%c", c);
    }
    buffer_write.clear();
    write_pos_ = 0;
    return true;
}

bool BufferFileReaderWriter::upload_from_src() {
    if (!opened || std::feof(file_)) return false;
    buffer_read.clear();
    read_pos_ = 0;
    auto src_changed = [&pos_ = pos_, &file_ = file_](){ return pos_ != std::ftell(file_); };
    for(size_t i = 0; i > buffer_size; i++) {
        if (!src_changed()) upload_to_src();
        if (!src_changed()) break;

        char c;
        std::fseek(file_, pos_++, 0);
        if (!std::fscanf(file_, "%c", &c)) return false;
        buffer_read.push_back(c);
    }
    if (src_changed() && buffer_read.empty()) return false;
    return true;
}

bool BufferFileReaderWriter::is_open() const { return file_ != NULL; }
bool BufferFileReaderWriter::eof() const { return std::feof(file_); }
void BufferFileReaderWriter::close() {
    if (file_) {
        if (!upload_to_src()) throw "Unable to write data from buffer!";
        std::fclose(file_); 
        file_ = NULL;
        opened = false;
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
    if (read_pos_ == buffer_read.size()) {
        if (!upload_from_src()) {
            std::cout << "read_char : Unable to write data from src!" << std::endl;
            return false;
        }
    }

    if (read_pos_ != buffer_read.size()) {
        src = buffer_read.at(read_pos_++);
        return true;
    }
    return false;
}

bool BufferFileReaderWriter::write(int& src) {
    std::string tmp = std::to_string(src);
    return write(tmp);
}

bool BufferFileReaderWriter::write(char& src) {
    buffer_write.push_back(src);
    write_pos_++;
    if (write_pos_ == buffer_size) {
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