#pragma onece

class Point {
public:
    Point(float x, float y);
    float get_x() const;
    float get_y() const;
private:
    float x_coord;
    float y_coord;
};

float Point::get_x() const{ return Point::x_coord;};
float Point::get_y() const{ return Point::y_coord;};

Point::Point(float x, float y){
    x_coord = x;
    y_coord = y;
}

