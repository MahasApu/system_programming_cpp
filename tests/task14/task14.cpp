
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include "../../tasks/task14/TinyAllocator.hpp"


struct Point {
    int x, y;
    Point(int x, int y): x(x), y(y) { }
    Point(const Point& other): x(other.x), y(other.y) { std::cout << "Copy costructor was called" << std::endl; };
    Point(const Point&& other): x(other.x), y(other.y) { std::cout << "Move costructor was called" << std::endl; };
    Point& operator=(const Point& other) {
        std::cout << "Assignment operator was called" << std::endl;
        x = other.x;
        y = other.y;
        return *this;
    };

    friend std::ostream& operator<<(std::ostream& o, const Point& other) {
        o << other.x << " " << other.y;
        return o;
    }   
    ~Point() { std::cout << "Destructor was called" << std::endl;};
};


TEST(TinyAllocator, test1) {

    int a = 10;
    double b = 11;
    char c = 's';
    Point p(1,2);

    const size_t size = sizeof(a) + sizeof(b) + sizeof(c) + sizeof(p);
    char mem[size];

    allocate<sizeof(mem)>(mem, a, b, c, p);

    int* a_ = (int*) (mem);
    double* b_ = (double*) (mem + sizeof(int));
    char* c_ = (char*) (mem + sizeof(int) + sizeof(double));
    Point* p_ = (Point*) (mem + sizeof(int) + sizeof(double) + sizeof(Point));

    ASSERT_TRUE(a == *a_);
    ASSERT_TRUE(b == *b_);
    ASSERT_TRUE(c == *c_);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}