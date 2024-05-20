#pragma once 

#include "MixInCounterException.hpp"

template <size_t LIMIT>
class MixInCounter {
    static inline size_t counter = 0;
public:
    MixInCounter() {
        if (counter >= LIMIT) throw MixInCounterException("Max number of instances reached!");
        counter++;
    }

    MixInCounter(const MixInCounter& other) {
        if (counter >= LIMIT) throw MixInCounterException("Max number of instances reached!");
        counter++;
    }
    ~MixInCounter() { counter--;}
};