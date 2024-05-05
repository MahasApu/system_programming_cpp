#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../tasks/task11/GetPrimes.hpp"

size_t primes[] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};

TEST(PrimesTest, first) {
    ASSERT_TRUE( primes[1] == prime<1>::value);
}

TEST(PrimesTest, second) {
    ASSERT_TRUE( primes[2] == prime<2>::value);
}

TEST(PrimesTest, third) {
    ASSERT_TRUE( primes[3] == prime<3>::value);
}

TEST(PrimesTest, fourth) {
    ASSERT_TRUE( primes[4] == prime<4>::value);
}

TEST(PrimesTest, fifth) {
    ASSERT_TRUE( primes[5] == prime<5>::value);
}

TEST(PrimesTest, sixth) {
    ASSERT_TRUE( primes[6] == prime<6>::value);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
