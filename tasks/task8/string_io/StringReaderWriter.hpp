#pragma once

#include "../ReaderWriter.hpp"

class StringReaderWriter: public ReaderWriter {
    std::string const& str_;
    size_t pos_;
public:
    StringReaderWriter(std::string& str) : str_(str), pos_(0) { }
    ~StringReaderWriter() { }
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
