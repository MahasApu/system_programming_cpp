
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include "../../tasks/task14/TinyAllocator.hpp"


TEST(TinyAllocator, test1) {

    int a = 10;
    double b = 11;
    char c = 's';

    const size_t size = sizeof(a) + sizeof(b) + sizeof(c);
    char mem[size];

    allocate<sizeof(mem)>(mem, a, b, c);

    int* a_ = (int*) (mem);
    double* b_ = (double*) (mem + sizeof(int));
    char* c_ = (char*) (mem + sizeof(int) + sizeof(double));

    ASSERT_TRUE(a == *a_);
    ASSERT_TRUE(b == *b_);
    ASSERT_TRUE(c == *c_);
}

int main() {

}