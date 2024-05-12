#pragma once

#include "../../ReaderWriter.hpp"

class StringReaderWriter: virtual public ReaderWriter {
    std::string& str_;
    bool opened;
public:
    StringReaderWriter(std::string& str) : str_(str), opened(true) { }
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
