#include "StringReader.hpp"

bool StringReader::is_open() const{ return opened_;}
bool StringReader::eof() const { return pos_ >= str_.size() - 1; }
void StringReader::close() { opened_ = true; }

bool StringReader::read(char& buf) {
    if (!opened_ || ++pos_ >= str_.size()) return false;
    buf = str_[pos_];
    return true;
}
bool StringReader::read(int& buf) {
    if (read(buf)) {
        buf -= '0';
        return true;
    }
    return false;
}
bool StringReader::read(std::string& str) {
    if (!opened_ || str_.empty()) return false;
    str = str_;
    return true;
 }
