#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "/mnt/c/Users/vaskm/OneDrive/Рабочий стол/2024/system_programming_cpp/tasks/second/Line.h"
#include <boost/function.hpp>


TEST(LineTest, lineConstructors12) {
    Line* line1 = new Line{-1, 1, 0};
    Line* line2 = new Line{Point{1, 1}, Point{2, 2}};

    ASSERT_TRUE(line1->get_dy() == line2->get_dy());
    ASSERT_TRUE(line1->get_dx() == line2->get_dx());
    ASSERT_TRUE(line1->get_tan() == line2->get_tan());
    ASSERT_TRUE(line1->get_bias() == line2->get_bias());

    delete line1;
    delete line2;

}

TEST(LineTest, lineConstructors13) {
    Line* line1 = new Line{-1, 1, 0};
    Line* line3 = new Line{Point{2, 2}, -1, 1};

    ASSERT_TRUE(line1->get_dy() == line3->get_dy());
    ASSERT_TRUE(line1->get_dx() == line3->get_dx());
    ASSERT_TRUE(line1->get_tan() == line3->get_tan());
    ASSERT_TRUE(line1->get_bias() == line3->get_bias());

    delete line1;
    delete line3;
}

TEST(LineTest, lineConstructors23) {
    Line* line2 = new Line{Point{1, 1}, Point{2, 2}};
    Line* line3 = new Line{Point{2, 2}, -1, 1};

    ASSERT_TRUE(line2->get_dy() == line3->get_dy());
    ASSERT_TRUE(line2->get_dx() == line3->get_dx());
    ASSERT_TRUE(line2->get_tan() == line3->get_tan());
    ASSERT_TRUE(line2->get_bias() == line3->get_bias());

    delete line2;
    delete line3;
}


TEST(LineTest, intersectionCollinear) {
    Line* line2 = new Line{Point{1, 1}, Point{2, 2}};
    ASSERT_TRUE(line2->lines_intersection(Line{Point{2, 2}, -2, 2}) == nullptr);
    delete line2;
}

TEST(LineTest, intersection) {
    Line* line2 = new Line{1, -1, 0};
    Point* actual = line2->lines_intersection(Line{1, 0, 0});
    Point* expected = new Point{0, 0};

    ASSERT_TRUE(actual->get_x() == expected->get_x());
    ASSERT_TRUE( actual->get_y() == expected->get_y());

    delete line2;
    delete actual;
    delete expected;
}

TEST(LineTest, perpendicular) {
    Line* line2 = new Line{1, 1, 0};
    Line* actual = line2->perpendicular(Point{0, 0});
    Line* expected = new Line{-1, 1, 0};

    ASSERT_TRUE(actual->get_dx() == expected->get_dx());
    ASSERT_TRUE( actual->get_dy() == expected->get_dy());

    delete line2;
    delete actual;
    delete expected;
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}