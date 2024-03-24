#include <iostream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../tasks/fifth/Triple.hpp"
#include "../../tasks/fifth/ScopedPointerDeepCopy.hpp"
#include "../../tasks/fifth/ScopedPointerProhibited.hpp"

// First one with deep copy
// Second one with transferring an ownership (prohibit copy cstr)


TEST(DeepCopy, copyConstructor) {

    ScopedPointerDeepCopy sp{new Triple{1, 2, 3}};
    ScopedPointerDeepCopy sp2 = sp;
    ASSERT_TRUE(sp.get() != std::nullopt);
}


TEST(DeepCopy, moveConstructor) {

    ScopedPointerDeepCopy sp{new Triple{1, 2, 3}};
    ScopedPointerDeepCopy sp2 {std::move(sp)};
    ASSERT_TRUE(sp.get() == std::nullopt);
}


TEST(DeepCopy, copyOperator) {

    ScopedPointerDeepCopy sp1{new Triple{1, 2, 3}};
    ScopedPointerDeepCopy sp2{new Triple{1, 2, 3}};
    sp2 = sp1;
    ASSERT_TRUE(sp1.get() != std::nullopt);
}

TEST(DeepCopy, moveOperator) {

    ScopedPointerDeepCopy sp1{new Triple{1, 2, 3}};
    ScopedPointerDeepCopy sp2{new Triple{1, 2, 3}};
    sp2 = std::move(sp1);
    ASSERT_TRUE(sp1.get() == std::nullopt);
}


TEST(Prohibited, copyConstructor) {

    ScopedPointerProhibited sp{new Triple{1, 2, 3}};
    // ScopedPointerProhibited sp2 = sp; - compilation error
    ScopedPointerProhibited sp2  = std::move(sp);
    ASSERT_TRUE(sp.get() == std::nullopt);
}


TEST(Prohibited, moveConstructor) {

    ScopedPointerProhibited sp{new Triple{1, 2, 3}};
    ScopedPointerProhibited sp2 {std::move(sp)};
    ASSERT_TRUE(sp.get() == std::nullopt);
}


TEST(Prohibited, copyOperator) {

    ScopedPointerProhibited sp1{new Triple{1, 2, 3}};
    ScopedPointerProhibited sp2{new Triple{1, 2, 3}};
    // sp2 = sp1; - compilation error due to call of copy constructor
    sp2 = std::move(sp1);
    ASSERT_TRUE(sp1.get() == std::nullopt);
}

TEST(Prohibited, moveOperator) {

    ScopedPointerProhibited sp1{new Triple{1, 2, 3}};
    ScopedPointerProhibited sp2{new Triple{1, 2, 3}};
    sp2 = std::move(sp1);
    ASSERT_TRUE(sp1.get() == std::nullopt);
}


TEST(Overloading, operatorsOverloading) {

    ScopedPointerDeepCopy sp1{new Triple{1, 2, 3}};
    ASSERT_TRUE(sp1->first == 1);
    ASSERT_TRUE(sp1->second == 2);
    ASSERT_TRUE(sp1->third == 3);
}


int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}