#pragma once
#include "Point.hpp"
#include <optional>


/*
*     y = tan * x + bias'
*     or 
*    -dy*y = dx*x + bias
*/

class Line {
    
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
    std::optional<Point> lines_intersection(const Line& line);
    Line perpendicular(const Point& point);
};
