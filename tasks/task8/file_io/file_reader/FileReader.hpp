#pragma once
#include "../../Reader.hpp"

class FileReader: public Reader {
    bool read(char& buf) override;
    bool read(int& buf) override;
    bool read(std::string& str) override;

};