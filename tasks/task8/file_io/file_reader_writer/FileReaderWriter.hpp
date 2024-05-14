#pragma once

#include "../../ReaderWriter.hpp"

class FileReaderWriter: public ReaderWriter {
    FILE* file_;
public:
    FileReaderWriter(const std::string& src_name) {file_ = std::fopen(src_name.c_str(), "r+");} 
    ~FileReaderWriter() { if (file_ != NULL) close(); }
    bool is_open() const override;
    bool eof() const override;
    void close() override;

    bool read(int& src) override;
    bool read(char& src) override;
    bool read(std::string& src) override;

    bool write(int& src) override;
    bool write(char& src) override;
    bool write(std::string& src) override;

};