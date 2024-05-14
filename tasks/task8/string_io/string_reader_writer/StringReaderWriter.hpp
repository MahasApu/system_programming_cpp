#pragma once

#include "../../ReaderWriter.hpp"

class StringReaderWriter: public ReaderWriter {
    std::string& str_;
    bool opened;
public:
    StringReaderWriter(std::string& src) : str_(src), opened(true) { }
    ~StringReaderWriter() { close(); }
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
