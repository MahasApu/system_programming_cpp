#pragma once
#include "Point.h"
#include "iostream"


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


Line::Line(const Point& start, const Point& end) {
    this->dy = - (end.get_y() - start.get_y());
    this->dx = end.get_x()- start.get_x();
    this->tan = -this->dy / this->dx;
    this->bias = start.get_y() - this->tan * start.get_x();
}

Line::Line(const Point& point, float dy, float dx) {
    this->dy = dy;
    this->dx = dx;
    this->tan = -dy / dx;
    this->bias = point.get_y() - tan * point.get_x();
}

Line::Line(float dy, float dx, float bias) {
    this->dy = dy;
    this->dx = dx;
    this->tan = -dy / dx;
    this->bias = bias / this->dy;
}

float Line::get_dy() { return this->dy;}
float Line::get_dx() { return this->dx;}
float Line::get_tan() { return this->tan;}
float Line::get_bias() { return this->bias;}

Point* Line::lines_intersection(const Line& line) {
    float determ = this->tan - line.tan;
    if (determ == 0.0) return NULL;
    
    //(dx/dy)x + (bias/dy) = (dx'/dy')x + (bias'/dy')
    // tan*x   +   bias    =   tan'*x   +  bias'  
    // x = (bias' - bias)/(tan - tan')

    float inter_x = (line.bias - this->bias) / (this->tan - line.tan);
    float inter_y = this->tan * inter_x + this->bias;
    return new Point(inter_x, inter_y);
}

Line* Line::perpendicular(const Point& point) {
    // tan + pi/2 -> rotation by 90 degree
    // tan + pi/2 = - ctg
    // - ctg = - dy/dx
    float bias = dx * point.get_y() - dy * point.get_x();
    return new Line(-this->dx, this->dy, bias);
}
