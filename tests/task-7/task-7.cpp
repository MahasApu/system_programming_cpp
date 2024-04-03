#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../tasks/task-7/Binary/Add.hpp"
#include "../../tasks/task-7/Unary/Val.hpp"
#include "../../tasks/task-7/Unary/Var.hpp"


TEST(ExpressionsInheritance, varTest) {
    Expression* v = new Add(new Var("x"), new Val(10));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


