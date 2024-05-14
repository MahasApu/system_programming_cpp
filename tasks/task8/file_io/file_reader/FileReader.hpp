#pragma once
#include "../../Reader.hpp"

class FileReader: public Reader {
    FILE* file_;
    size_t pos_;
    bool opened_;
public:
    FileReader(const std::string& src_name) {file_ = std::fopen(src_name.c_str(), "w");} 
    ~FileReader() { if (file_ != NULL) close(); }
    bool is_open() const override;
    bool eof() const override;
    void close() override;

    bool read(char& src) override;
    bool read(int& src) override;
    bool read(std::string& src) override;

};