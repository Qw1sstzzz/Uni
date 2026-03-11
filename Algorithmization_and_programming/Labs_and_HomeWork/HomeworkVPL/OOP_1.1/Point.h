#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cassert>
#include <cmath>

class Point {
public:
    Point() : x_(0.0), y_(0.0) {};

    Point(double x0, double y0) : x_(x0), y_(y0) {
        assert(!std::isnan(x_) && !std::isinf(x_));
        assert(!std::isnan(y_) && !std::isinf(y_));
    };

    Point(const Point& object) : x_(object.x_), y_(object.y_) {};

    ~Point() {};

    void setX(const double x);
    void setY(const double y);

    double getX() const;
    double getY() const;

    bool isEqual(const Point& object) const;
    double getDistance(const Point& object) const;
    void move(const int k);

private:
    double x_{ 0.0 };   
    double y_{ 0.0 };   
};

bool isPointInCircle(const Point& p, double r);
void input(Point& p);
void output(const Point& p);

#endif