#pragma once 

#include <iostream>

template <typename Checker, typename... Args>
int getIndexOfTheFirstMatch(Checker checker, Args... args) {
    size_t counter = 0;
    int result = -1;
    bool found = ((checker(std::forward<Args>(args)) ? (result = counter, false) : (counter++, true)) && ...);
    return result;
}