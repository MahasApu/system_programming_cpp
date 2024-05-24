#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../tasks/task15/Container.hpp"

struct Point {
    int x, y;
    Point(int x, int y): x(x), y(y) { }
    Point(const Point& other): x(other.x), y(other.y) { std::cout << "Copy costructor was called" << std::endl; };
    Point(const Point&& other): x(other.x), y(other.y) { std::cout << "Move costructor was called" << std::endl; };
    Point& operator=(const Point& other) {
        std::cout << "Assignment operator was called" << std::endl;
        x = other.x;
        y = other.y;
        return *this;
    };

    friend std::ostream& operator<<(std::ostream& o, const Point& other) {
        o << other.x << " " << other.y;
        return o;
    }   
    ~Point() { std::cout << "Destructor was called" << std::endl;};
};

TEST(Container, getElement) {
    Container<int, char, Point> c(12, 'c', std::move(Point{2 ,3}));
    ASSERT_TRUE(c.getElement<int>(0) == 12);
    ASSERT_TRUE(c.getElement<char>(1) == 'c');
    ASSERT_TRUE(c.getElement<Point>(2).x == 2);
    ASSERT_TRUE(c.getElement<Point>(2).y == 3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}