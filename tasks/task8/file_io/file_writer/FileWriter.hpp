#pragma once
#include "../../Writer.hpp"

class FileWriter: public Writer {
    FILE* file_;
    size_t pos_;
    bool opened;
public:
    FileWriter(const std::string& src_name) {file_ = std::fopen(src_name.c_str(), "w");} 
    ~FileWriter() { if (file_ != NULL) close(); }
    bool is_open() const override;
    bool eof() const override;
    void close() override;

    bool write(char& src) override;
    bool write(int& src) override;
    bool write(std::string& src) override;
};