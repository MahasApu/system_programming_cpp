#include "../../tasks/sixth/SquareMatrix.hpp"
#include <vector>

int main() {
    std::vector<double> vector = {1,2,3,4,5};
    SquareMatrix matrix(vector);
    SquareMatrix m = matrix + 10;
    m.print_matrix();
    double summ = (double) m;
    std::cout << summ;
}