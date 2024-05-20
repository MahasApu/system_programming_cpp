#include "../../tasks/task14/TinyAllocator.hpp"


int main() {
    int a;
    double b;
    char c;
    allocate<100>(&a, a, b, c);
    return 0;
}