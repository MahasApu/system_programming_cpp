#pragma once
#include "../../Writer.hpp"

class FileWriter: public Writer {
    bool write(char& buf) override;
    bool write(int& buf) override;
    bool write(std::string& str) override;
};