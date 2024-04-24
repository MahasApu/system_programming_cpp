#include "StringReaderWriter.hpp"

bool StringReaderWriter::is_open() const { return true; }
bool StringReaderWriter::eof() const { return pos_ >= str_.size(); }
void StringReaderWriter::close() {}


bool StringReaderWriter::read(int& buf) { 
    return std::sscanf(str_.c_str(), "%d", &buf);
}

bool StringReaderWriter::read(char& buf) {
    return std::sscanf(str_.c_str(), "%c", &buf);
}

bool StringReaderWriter::read(std::string& str) {
    str = str_.substr(pos_);
    pos_ = str_.size();
    return true;
}

bool StringReaderWriter::write(int& buf) {
    std::string str = std::to_string(buf);
    return write(str);
}

bool StringReaderWriter::write(char& buf) {
    return write(buf);
}

bool StringReaderWriter::write(std::string& str) {
    if (pos_ + str.size() > str_.size()) {
        return false;
    }
    char c;
    for (size_t i = 0 ; i < str.size(); c = str.at(i++)) {
        write(c);
    }
    pos_ += str.size();
    return true;
}