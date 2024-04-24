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
    while( read(c)) { str.push_back(c); }
    return true;
}

bool FileReaderWriter::read(int& buf) {
    std::fseek(file_, pos_, 0);
    if (std::fscanf(file_, "%d", &buf) == 1) {
        pos_++;
        return true;
    }
    return false;
}

bool FileReaderWriter::read(char& buf) {
    std::fseek(file_, pos_, 0);
    if (std::fscanf(file_, "%c", &buf) == 1) {
        pos_++;
        return true;
    }
    return false;
}

bool FileReaderWriter::write(int& buf) {
    std::fseek(file_, 0, 1);
    std::fprintf(file_, "%d", buf);
    return !eof();
}

bool FileReaderWriter::write(char& buf) {
    std::fseek(file_, 0, 1);
    std::fprintf(file_, "%s", &buf);
    return !eof();
}

bool FileReaderWriter::write(std::string& str) {
    std::fseek(file_, 0, 1);
    return std::fprintf(file_, "%s", str.c_str());
}