#include "../../tasks/task15/Container.hpp"

struct Point;

int main() {
    Container<int, char, Point> c(12, 'c', Point{2 ,3});
    std::cout << c.getElement<int>(0) << std::endl;
    std::cout << c.getElement<char>(1) << std::endl;
    std::cout << c.getElement<Point>(2) << std::endl;
}