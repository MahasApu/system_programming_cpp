#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../tasks/task6/SquareMatrix.hpp"


TEST(SquareMatrix, diagConstructor) {

    SquareMatrix m1({1, 1, 1});
    ASSERT_TRUE((double)m1 == 3); 
}

TEST(SquareMatrix, copyConstructor) {

    SquareMatrix m1({1, 1, 1});
    SquareMatrix m2 = m1;
    ASSERT_TRUE((double)m1 == (double)m2);
}

TEST(SquareMatrix, moveConstructor) {

    SquareMatrix m1({1, 1, 1});
    SquareMatrix m2 = std::move(m1);
    ASSERT_TRUE((double)m1 == 0);
    ASSERT_TRUE((double)m2 == 3);
}


TEST(SquareMatrix, matrixOperators) {

    SquareMatrix m1({1, 1, 1});
    SquareMatrix m2({2, 2, 2});
    ASSERT_TRUE((double)(m1 - m2) == -3);
    ASSERT_TRUE((double)(m1 + m2) == 9);
    ASSERT_TRUE((double)(m1 * m2) == 6);
    ASSERT_FALSE(m1 == m2);
    ASSERT_TRUE(m1 != m2);

    m1 += m2;
    ASSERT_TRUE((double)m1 == 9);
    
    m1 *= m2;
    ASSERT_TRUE((double)m1 == 18);    
}


TEST(SquareMatrix, scalarOperators) {

    SquareMatrix m1({1, 1, 1});
    SquareMatrix m2(1);
    ASSERT_TRUE((double)(m1 - 2) == -3);
    ASSERT_TRUE((double)(m1 + 2) == 9);
    ASSERT_TRUE((double)(m1 * 2) == 6);

    m1 += 2;
    ASSERT_TRUE((double)m1 == 9);
    
    m1 *= 2;
    ASSERT_TRUE((double)m1 == 18);
    
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
