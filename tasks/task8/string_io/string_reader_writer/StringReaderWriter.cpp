#include "StringReaderWriter.hpp"

bool StringReaderWriter::is_open() const { return opened; }
bool StringReaderWriter::eof() const { return write_pos_ >= str_.size() || read_pos_ >= str_.size(); }
void StringReaderWriter::close() { opened = false; }

bool StringReaderWriter::read(char& buf) {
    if (str_.empty()) return false;
    buf = str_[read_pos_++];
    return true;
}

bool StringReaderWriter::read(int& buf) {
    char tmp;
    if (read(tmp)) buf = tmp - '0'; return true;
    return false;
}

bool StringReaderWriter::read(std::string& str) {
    str = str_.substr(read_pos_);
    read_pos_ += str_.size();
    return true;
}

bool StringReaderWriter::write(char& buf) {
    str_.push_back(buf);
    write_pos_++;
    return true;
}

bool StringReaderWriter::write(int& buf) {
    std::string str = std::to_string(buf);
    return write(str);
}

bool StringReaderWriter::write(std::string& str) {
    for (auto c: str) { write(c); }
    write_pos_ += str.size();
    return true;
}