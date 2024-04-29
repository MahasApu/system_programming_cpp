#pragma once
#include <iostream>

class MixInCounterException: public std::exception {
    std::string message;

public:
    MixInCounterException(const std::string& message): message(message) { }
    const char* what() const noexcept override { return message.c_str();}
};