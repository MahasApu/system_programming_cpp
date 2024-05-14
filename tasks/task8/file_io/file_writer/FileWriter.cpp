#include "FileWriter.hpp"

bool FileWriter::is_open() const { return file_ != NULL; }
bool FileWriter::eof() const { return std::feof(file_); }
void FileWriter::close() {
     std::fclose(file_); 
     file_ = NULL;
}

bool FileWriter::write(int& src) {
    std::fseek(file_, pos_, 0);
    pos_ += std::fprintf(file_, "%d", src);
    return !eof();
}

bool FileWriter::write(char& src) {
    std::fseek(file_, pos_, 0);
    pos_ += std::fprintf(file_, "%c", src);
    return !eof();
}

bool FileWriter::write(std::string& src) {
    std::fseek(file_, pos_, 0);
    pos_ += src.size();
    return std::fprintf(file_, "%s", src.c_str());
}