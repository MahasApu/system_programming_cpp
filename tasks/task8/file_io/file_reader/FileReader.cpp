#include "FileReader.hpp"


bool FileReader::is_open() const { return file_ != NULL; }
bool FileReader::eof() const { return std::feof(file_); }
void FileReader::close() {
     std::fclose(file_); 
     file_ = NULL;
}

bool FileReader::read(char& src) {
    std::fseek(file_, pos_, 0);
    if (std::fscanf(file_, "%c", &src) != EOF) {
        pos_++;
        return true;
    }
    src = '\0';
    return false;
}

bool FileReader::read(int& src) { 
    std::fseek(file_, pos_, 0);
    if (std::fscanf(file_, "%d", &src) != EOF) {
        pos_++;
        return true;
    }
    return false;
}
bool FileReader::read(std::string& src) {
    char c;
    src.clear();
    while(read(c)) src.push_back(c);
    return !src.empty();
}