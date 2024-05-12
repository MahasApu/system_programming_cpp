#include "FileReaderWriter.hpp"
#include <cstdio>

bool FileReaderWriter::is_open() const { return file_ != NULL; }
bool FileReaderWriter::eof() const { return std::feof(file_); }
void FileReaderWriter::close() {
     std::fclose(file_); 
     file_ = NULL;
}

bool FileReaderWriter::read(std::string& str) {
    char c;
    str.clear();
    while(read(c)) str.push_back(c);
    return !str.empty();
}

bool FileReaderWriter::read(int& buf) {
    std::fseek(file_, read_pos_, 0);
    if (std::fscanf(file_, "%d", &buf) != EOF) {
        read_pos_++;
        return true;
    }
    return false;
}

bool FileReaderWriter::read(char& buf) {
    std::fseek(file_, read_pos_, 0);
    if (std::fscanf(file_, "%c", &buf) != EOF) {
        read_pos_++;
        return true;
    }
    buf = '\0';
    return false;
}

bool FileReaderWriter::write(int& buf) {
    std::fseek(file_, write_pos_, 0);
    write_pos_ += std::fprintf(file_, "%d", buf);
    return !eof();
}

bool FileReaderWriter::write(char& buf) {
    std::fseek(file_, write_pos_, 0);
    write_pos_ += std::fprintf(file_, "%c", buf);
    return !eof();
}

bool FileReaderWriter::write(std::string& str) {
    std::fseek(file_, write_pos_, 0);
    write_pos_ += str.size();
    return std::fprintf(file_, "%s", str.c_str());
}