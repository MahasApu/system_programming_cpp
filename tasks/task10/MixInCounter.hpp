#pragma once

#include <cstdlib>

#include "MixInCounterException.hpp"

template <size_t LIMIT>
class MixInCounter {
    static size_t counter;
public:
    MixInCounter() {
        counter++;
        if (counter >= LIMIT) throw MixInCounterException("Max number of instances reached!");
    }
    ~MixInCounter() { counter--;}
};

template <size_t LIMIT>
size_t MixInCounter<LIMIT>::counter = 0;
