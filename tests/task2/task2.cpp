#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "../../tasks/task2/Line.hpp"
#include <boost/function.hpp>


TEST(LineTest, lineConstructors12) {

    Line line1 = Line{-1, 1, 0};
    Line line2 = Line{Point{1, 1}, Point{2, 2}};

    ASSERT_TRUE(line1.get_dy() == line2.get_dy());
    ASSERT_TRUE(line1.get_dx() == line2.get_dx());
    ASSERT_TRUE(line1.get_tan() == line2.get_tan());
    ASSERT_TRUE(line1.get_bias() == line2.get_bias());

}

TEST(LineTest, lineConstructors13) {
    Line line1 = Line{-1, 1, 0};
    Line line3 = Line{Point{2, 2}, -1, 1};

    ASSERT_TRUE(line1.get_dy() == line3.get_dy());
    ASSERT_TRUE(line1.get_dx() == line3.get_dx());
    ASSERT_TRUE(line1.get_tan() == line3.get_tan());
    ASSERT_TRUE(line1.get_bias() == line3.get_bias());
}

TEST(LineTest, lineConstructors23) {
    Line line2 = Line{Point{1, 1}, Point{2, 2}};
    Line line3 = Line{Point{2, 2}, -1, 1};

    ASSERT_TRUE(line2.get_dy() == line3.get_dy());
    ASSERT_TRUE(line2.get_dx() == line3.get_dx());
    ASSERT_TRUE(line2.get_tan() == line3.get_tan());
    ASSERT_TRUE(line2.get_bias() == line3.get_bias());
}


TEST(LineTest, intersectionCollinear) {
    Line line2 = Line{Point{1, 1}, Point{2, 2}};
    std::optional<Point> actual = line2.lines_intersection(Line{Point{2, 2}, -2, 2});
    
    ASSERT_FALSE(actual);
}

TEST(LineTest, intersection) {
    Line line2 = Line{1, -1, 0};
    std::optional<Point> actual = line2.lines_intersection(Line{1, 0, 0});
    ASSERT_TRUE(actual);
    Point expected = Point{0, 0};

    ASSERT_TRUE(actual.value().get_x() == expected.get_x());
    ASSERT_TRUE(actual.value().get_y() == expected.get_y());
}

TEST(LineTest, perpendicular) {
    Line line2 = Line{1, 1, 0};
    Line actual = line2.perpendicular(Point{0, 0});
    Line expected = Line{-1, 1, 0};

    ASSERT_TRUE(actual.get_dx() == expected.get_dx());
    ASSERT_TRUE( actual.get_dy() == expected.get_dy());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}