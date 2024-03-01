#pragma once
#include "Point.h"
#include <iostream>


class Line {

    //  y = tan * x + bias'
    //  or 
    // -dy*y = dx*x + bias
private:
    float dy, dx, tan, bias;
public:
    Line(const Point& start, const Point& end);
    Line(const Point& point, float dy, float dx);
    Line(float dy, float dx, float bias);
    float get_dy();
    float get_dx();
    float get_tan();
    float get_bias();
    Point* lines_intersection(const Line& line);
    Line* perpendicular(const Point& point);
};
