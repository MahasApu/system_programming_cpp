#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include "../../tasks/task13/GetFirstIndex.hpp"


bool checker(int a) {return a%2 == 0;}

TEST(GetFirstIndex, Found) {

  auto actual = getIndexOfTheFirstMatch([](auto a){ return a % 2 != 0; }, 6,2,6,4,1,8,6);
  ASSERT_TRUE(actual == 4);
}

struct Point {
    int x, y;
    Point(int x_, int y_): x(x_), y(y_) { }
    Point(const Point& other): x(other.x), y(other.y) { };
    Point(const Point&& other): x(other.x), y(other.y) {
      std::cout << "move cstr was called" << std::endl;
    };
    Point& operator=(Point other) {
        std::swap(x, other.x);
        std::swap(y, other.y);
        return *this;
    };

    friend std::ostream& operator<<(std::ostream& o, const Point& other) {
        o << other.x;
        o << " ";
        return o;
    }
    
    ~Point() {};
};

TEST(GetFirstIndex, NotFound) {

  auto actual = getIndexOfTheFirstMatch([](auto a){ return a % 2 != 0; }, 6,2,6,4,10,8,6);
  ASSERT_TRUE(actual == -1);
}

TEST(GetFirstIndex, forStruct) {

  // add struct with copy and move cstrs
  // take by val
  // pass all args as rval
  // move cstr should be called
  auto actual = getIndexOfTheFirstMatch([](Point p){ return p.x == 0; }, Point{1,2}, Point{4,8}, Point{0,1});
  ASSERT_TRUE(actual == 2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}