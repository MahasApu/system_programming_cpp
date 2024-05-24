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
    Point(int x, int y): x(x), y(y) { std::cout << "Default costructor was called" << std::endl; }
    Point(const Point& other): x(other.x), y(other.y) { std::cout << "Copy costructor was called" << std::endl; };
    Point(const Point&& other): x(other.x), y(other.y) { std::cout << "Move costructor was called" << std::endl; };
    Point& operator=(const Point& other) {
        std::cout << "Assignment operator was called" << std::endl;
        x = other.x;
        y = other.y;
        return *this;
    };

    Point& operator+( const Point& other) {
      x += other.x;
      y += other.y;
      return *this;
    }  
    friend std::ostream& operator<<(std::ostream& o, const Point& other) {
        o << other.x << " " << other.y;
        return o;
    }   
    ~Point() { std::cout << "destructor was called" << std::endl;};
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
  auto actual = getIndexOfTheFirstMatch([](Point p){ return p.x == 0; }, std::move(Point{1,2}), std::move(Point{4,8}), std::move(Point{0,1}));
  ASSERT_TRUE(actual == 2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}