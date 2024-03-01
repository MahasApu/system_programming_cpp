#pragma once

class Point {
private:
    float x_coord, y_coord;
public:
    Point(float x, float y): x_coord(x),
                             y_coord(y) {}
    float get_x() const { return this->x_coord;};
    float get_y() const { return this->y_coord;};

};


