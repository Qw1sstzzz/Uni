#include "Point.h"

#include <iostream>
#include <cassert>
#include <cmath>

void Point::setX(double x) {
    assert(!std::isnan(x) && !std::isinf(x));
    x_ = x;
} 

void Point::setY(double y) {
    assert(!std::isnan(y) && !std::isinf(y));
    y_ = y;
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

void Point::move(const int k) {
    x_ += k;
    y_ += k;
}

Point& Point::operator+=(int k) {
    x_ += k;
    y_ += k;
    return *this;
}

bool Point::operator==(const Point& p) const {
    return ((x_ == p.x_) && (y_ == p.y_));  
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x_ << "," << p.y_ << ")";
    return os;
}
 
std::istream& operator>>(std::istream& is, Point& p) {
    is >> p.x_ >> p.y_;
    return is;
}