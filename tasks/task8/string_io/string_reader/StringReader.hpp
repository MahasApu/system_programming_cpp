#pragma once
#include "../../Reader.hpp"

class StringReader: public Reader {
    std::string& str_;
    size_t pos_;
    bool opened_;

public:

    StringReader(std::string& str): str_(str), pos_(-1), opened_(true) { }
    bool is_open() const override;
    bool eof() const override;
    void close() override;

    bool read(char& buf) override;
    bool read(int& buf) override;
    bool read(std::string& str) override;
};