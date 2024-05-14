#include "FileReaderWriter.hpp"
#include <cstdio>

bool FileReaderWriter::is_open() const { return file_ != NULL; }
bool FileReaderWriter::eof() const { return std::feof(file_); }
void FileReaderWriter::close() {
     std::fclose(file_); 
     file_ = NULL;
}

bool FileReaderWriter::read(std::string& src) {
    char c;
    src.clear();
    while(read(c)) src.push_back(c);
    return !src.empty();
}

bool FileReaderWriter::read(int& src) {
    std::fseek(file_, read_pos_, 0);
    if (std::fscanf(file_, "%d", &src) != EOF) {
        read_pos_++;
        return true;
    }
    return false;
}

bool FileReaderWriter::read(char& src) {
    std::fseek(file_, read_pos_, 0);
    if (std::fscanf(file_, "%c", &src) != EOF) {
        read_pos_++;
        return true;
    }
    src = '\0';
    return false;
}

bool FileReaderWriter::write(int& src) {
    std::fseek(file_, write_pos_, 0);
    write_pos_ += std::fprintf(file_, "%d", src);
    return !eof();
}

bool FileReaderWriter::write(char& src) {
    std::fseek(file_, write_pos_, 0);
    write_pos_ += std::fprintf(file_, "%c", src);
    return !eof();
}

bool FileReaderWriter::write(std::string& src) {
    std::fseek(file_, write_pos_, 0);
    write_pos_ += src.size();
    return std::fprintf(file_, "%s", src.c_str());
}