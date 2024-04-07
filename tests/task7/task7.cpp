#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../tasks/task7/binary/Add.hpp"
#include "../../tasks/task7/binary/Sub.hpp"
#include "../../tasks/task7/binary/Exponent.hpp"
#include "../../tasks/task7/binary/Mult.hpp"
#include "../../tasks/task7/binary/Div.hpp"
#include "../../tasks/task7/unary/Val.hpp"
#include "../../tasks/task7/unary/Var.hpp"
#include "../../tasks/task7/ScopedExpression.hpp"



TEST(ExpressionsInheritance, valTest) {
    ScopedExpression v(new Val(10));
    ASSERT_TRUE(ScopedExpression(v->diff("x"))->get_symbolic() == "0");
    ASSERT_TRUE(ScopedExpression(v->diff("y"))->get_symbolic() == "0");
}

TEST(ExpressionsInheritance, varTest) {
    ScopedExpression v(new Var("x"));
    ASSERT_TRUE(ScopedExpression(v->diff("x"))->get_symbolic() == "1");
    ASSERT_TRUE(ScopedExpression(v->diff("y"))->get_symbolic() == "0");
}


TEST(ExpressionsInheritance, addTest) {
    ScopedExpression v(new Add(new Var("10"), new Val(10)));
    ASSERT_TRUE(ScopedExpression(v->diff("x"))->get_symbolic() == "0+0");
    ASSERT_TRUE(ScopedExpression(v->diff("y"))->get_symbolic() == "0+0");
}

TEST(ExpressionsInheritance, subTest) {
    ScopedExpression v(new Sub(new Var("10"), new Val(10)));
    ASSERT_TRUE(ScopedExpression(v->diff("x"))->get_symbolic() == "0-0");
    ASSERT_TRUE(ScopedExpression(v->diff("y"))->get_symbolic() == "0-0");
}


TEST(ExpressionsInheritance, divTestInt) {
    ScopedExpression v(new Div(new Var("x"), new Val(10)));
    ASSERT_TRUE(ScopedExpression(v->diff("x"))->get_symbolic() == "(1*10-x*0)/(10*10)");
}

TEST(ExpressionsInheritance, divTestVar) {
    ScopedExpression v(new Div(new Var("x"), new Var("y")));
    ASSERT_TRUE(ScopedExpression(v->diff("x"))->get_symbolic() == "(1*y-x*0)/(y*y)");
    ASSERT_TRUE(ScopedExpression(v->diff("y"))->get_symbolic() == "(0*y-x*1)/(y*y)");
}


TEST(ExpressionsInheritance, exponentTest) {
    ScopedExpression v(new Exponent(new Val(3)));
    ASSERT_TRUE(v->get_symbolic() == "e^3");
    ASSERT_TRUE(ScopedExpression(v->diff("x"))->get_symbolic() == "0*e^3");
}


TEST(ExpressionsInheritance, multTest) {
    ScopedExpression v(new Mult(new Var("x"), new Val(3)));
    ASSERT_TRUE(v->get_symbolic() == "x*3");
    ASSERT_TRUE(ScopedExpression(v->diff("x"))->get_symbolic() == "1*3+x*0");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


