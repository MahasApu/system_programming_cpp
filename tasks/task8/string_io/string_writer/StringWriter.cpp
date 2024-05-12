# include "StringWriter.hpp"
#include <string>

bool StringWriter::is_open() const { return opened_;}
bool StringWriter::eof() const { return false; }
void StringWriter::close() {opened_ = false; }

bool StringWriter::write(char& buf) {
    if (!opened_) return false;
    str_.push_back(buf);
    return true;
}

bool StringWriter::write(int& buf) {
    std::string tmp = std::to_string(buf);
    return write(tmp);
}

bool StringWriter::write(std::string& str) {
    for (auto c: str) {
        if (write(c)) continue;
        else return false;
    } 
    return true;
}
