#include "Line.h"


int main() {
    
    // Line* line2 = new Line{Point{2, 2}, Point{4, 4}};
    // Point* actual = line2->lines_intersection(Line{1, -1, 4});
    // if (actual != NULL) std::cout<< actual->get_x()<< actual->get_y() << std::endl;
    // Point* expected = new Point{-0.25, -0.25};

    Line* line2 = new Line{1, 1, 0};
    Line* actual = line2->perpendicular(Point{0, 0});
    Line* expected = new Line{-1, 1, 0};

    std::cout<< actual->get_dy()<< actual->get_dx() << std::endl;

}