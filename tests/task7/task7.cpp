#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../tasks/task7/binary/Add.hpp"
#include "../../tasks/task7/binary/Sub.hpp"
#include "../../tasks/task7/binary/Exponent.hpp"
#include "../../tasks/task7/binary/Mult.hpp"
#include "../../tasks/task7/binary/Div.hpp"
#include "../../tasks/task7/unary/Val.hpp"
#include "../../tasks/task7/unary/Var.hpp"



TEST(ExpressionsInheritance, valTest) {
    Expression* v = new Val(10);
    ASSERT_TRUE(v->diff("x")->get_expr() == "0");
    ASSERT_TRUE(v->diff("y")->get_expr() == "0");
    delete v;
}

TEST(ExpressionsInheritance, varTest) {
    Expression* v = new Var("x");
    ASSERT_TRUE(v->diff("x")->get_expr() == "1");
    ASSERT_TRUE(v->diff("y")->get_expr() == "0");
    delete v;
}


TEST(ExpressionsInheritance, addTest) {
    Expression* v = new Add(new Var("10"), new Val(10));
    ASSERT_TRUE(v->diff("x")->get_expr() == "0+0");
    ASSERT_TRUE(v->diff("y")->get_expr() == "0+0");
    delete v;
}

TEST(ExpressionsInheritance, subTest) {
    Expression* v = new Sub(new Var("10"), new Val(10));
    ASSERT_TRUE(v->diff("x")->get_expr() == "0-0");
    ASSERT_TRUE(v->diff("y")->get_expr() == "0-0");
    delete v;
}


TEST(ExpressionsInheritance, divTestInt) {
    Expression* v = new Div(new Var("x"), new Val(10));
    ASSERT_TRUE(v->diff("x")->get_expr() == "(1*10-x*0)/(10^2)");
    delete v;
}

TEST(ExpressionsInheritance, divTestVar) {
    Expression* v = new Div(new Var("x"), new Var("y"));
    ASSERT_TRUE(v->diff("x")->get_expr() == "(1*y-x*0)/(y^2)");
    ASSERT_TRUE(v->diff("y")->get_expr() == "(0*y-x*1)/(y^2)");
    delete v;
}


TEST(ExpressionsInheritance, exponentTest) {
    Expression* v = new Exponent(new Var("x"), new Val(3));
    ASSERT_TRUE(v->get_expr() == "x^3");
    ASSERT_TRUE(v->diff("x")->get_expr() == "3*x^2");
    delete v;
}


TEST(ExpressionsInheritance, multTest) {
    Expression* v = new Mult(new Var("x"), new Val(3));
    ASSERT_TRUE(v->get_expr() == "x*3");
    ASSERT_TRUE(v->diff("x")->get_expr() == "1*3+x*0");
    delete v;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


