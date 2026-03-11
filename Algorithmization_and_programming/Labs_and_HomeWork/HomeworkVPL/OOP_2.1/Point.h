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

    Point& operator+=(int k);
    bool operator==(const Point& object) const;
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    friend std::istream& operator>>(std::istream& is, Point& p);

private:
    double x_{ 0.0 };   
    double y_{ 0.0 };   
};

#endif