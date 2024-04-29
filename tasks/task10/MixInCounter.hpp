#pragma once 

#include "MixInCounterException.hpp"

template <size_t LIMIT>
class MixInCounter {
    inline static size_t counter = 0;
public:
    MixInCounter() {
        if (counter >= LIMIT) throw MixInCounterException("Max number of instances reached!");
        counter++;
    }
    ~MixInCounter() { counter--;}
};