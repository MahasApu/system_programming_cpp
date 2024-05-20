#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include "../../tasks/task13/GetFirstIndex.hpp"


bool checker(int a) {return a%2 == 0;}

TEST(GetFirstIndex, Found) {

  auto actual = getIndexOfTheFirstMatch([](auto a){ return a % 2 != 0; }, 6,2,6,4,1,8,6);
  ASSERT_TRUE(actual == 4);
}

TEST(GetFirstIndex, NotFound) {

  auto actual = getIndexOfTheFirstMatch([](auto a){ return a % 2 != 0; }, 6,2,6,4,10,8,6);
  ASSERT_TRUE(actual == -1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}