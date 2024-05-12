#pragma once

#include "../../ReaderWriter.hpp"

class FileReaderWriter: virtual public ReaderWriter {
    FILE* file_;
public:
    FileReaderWriter(const std::string& filename) {file_ = std::fopen(filename.c_str(), "r+");} 
    ~FileReaderWriter() { if (file_ != NULL) close(); }
    bool is_open() const override;
    bool eof() const override;
    void close() override;

    bool read(int& buf) override;
    bool read(char& buf) override;
    bool read(std::string& str) override;

    bool write(int& buf) override;
    bool write(char& buf) override;
    bool write(std::string& str) override;

};