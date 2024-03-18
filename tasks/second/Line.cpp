#include "Line.hpp"

const double EPSILON = std::numeric_limits<double>::epsilon();

Line::Line(const Point& start, const Point& end) {
    this->dy = - (end.get_y() - start.get_y());
    this->dx = end.get_x()- start.get_x();
    this->tan = - this->dy / this->dx;
    this->bias = (start.get_y() - this->tan * start.get_x());
}

Line::Line(const Point& point, float dy, float dx) {
    this->dy = dy;
    this->dx = dx;
    this->tan = - this->dy / this->dx;
    this->bias = (point.get_y() - tan * point.get_x());
}

Line::Line(float dy, float dx, float bias) {
    this->dy = dy;
    this->dx = dx;
    this->tan = - this->dy / this->dx;
    this->bias = bias / this->dy;
}

float Line::get_dy() { return this->dy;}
float Line::get_dx() { return this->dx;}
float Line::get_tan() { return this->tan;}
float Line::get_bias() { return this->bias;}



/*
*    (dx/dy)x + (bias/dy) = (dx'/dy')x + (bias'/dy')
*    tan*x   +   bias    =   tan'*x   +  bias'  
*    x = (bias' - bias)/(tan - tan')
*/

std::optional<Point> Line::lines_intersection(const Line& line) {
    float determ = this->tan - line.tan;
    if (determ < EPSILON) return std::nullopt;

    float inter_x = (line.bias - this->bias) / (this->tan - line.tan);
    float inter_y = this->tan * inter_x + this->bias;
    return Point{inter_x, inter_y};
}


/*
*    tan + pi/2 -> rotation by 90 degree
*    tan + pi/2 = - ctg
*    - ctg = - dx/dy
*    y = (tan + pi/2)*x + bias = -dx/dy * x + bias
*    - dx * y + dy * x = bias
*/

Line Line::perpendicular(const Point& point) {
    float bias = this->dx * point.get_y() - this->dy * point.get_x();
    return Line(-this->dx, this->dy, bias);
}