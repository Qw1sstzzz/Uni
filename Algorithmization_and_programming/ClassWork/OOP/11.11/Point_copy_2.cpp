#include "Point.h"

#include <iostream>
#include <cassert>
#include <cmath>

Point& Point::setX(double x) {
    assert(!std::isnan(x) && !std::isinf(x));
    x_ = x;
    return *this;
} 

Point& Point::setY(double y) {
    assert(!std::isnan(y) && !std::isinf(y));
    y_ = y;
    return *this;
} 

double Point::getX() const {
    return x_;
} 

double Point::getY() const {
    return y_;
} 

bool Point::isEqual(const Point& obj) const {
    return (x_ == obj.x_ && y_ == obj.y_);
}

double Point::getDistance(const Point& obj) const {
    return sqrt((obj.x_ - x_)*(obj.x_ - x_) + (obj.y_ - y_)*(obj.y_ - y_));
}

Point& Point::move(const int k) {
    x_ += k;
    y_ += k;
    return *this;
}

bool isPointInCircle(const Point& p, double r) {
    // double d = p.getDistance(Point(0, 0));
    // return (d <= r);
    double dist_sq = p.x_ * p._x + p.y_ * p.y_;
    return dist_sq <= r*r;
}

void input(Point& p) {
    std::cout << "Enter your position" << std::endl;
    int x_int, y_int;
    std::cin >> x_int >> y_int;
    // p.setX((double)(x_int));
    // p.setY((double)(y_int));
    p.x_ = (double)(x_int);
    p.y_ = (double)(y_int);
}

void output(const Point& p) {
    std::cout << "(" << p.x_ << ", " << p.y_ << ")\n";
}