#pragma once
#include "../../Writer.hpp"

class StringWriter: public Writer {
    std::string& str_;
    size_t pos_;
    bool opened_;

public:
    StringWriter(std::string& str): str_(str), pos_(-1), opened_(true) { }
    bool is_open() const override;
    bool eof() const override;
    void close() override;

    bool write(char& buf) override;
    bool write(int& buf) override;
    bool write(std::string& str) override;
};