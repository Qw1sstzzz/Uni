#include "Point.h"
#include <cmath>
#include <cassert>
#include <stdexcept>

Point::Point() : x_(0.0), y_(0.0) {}

Point::Point(double x, double y) : x_(x), y_(y) {
    assert(!std::isnan(x) && !std::isnan(y));
}

double Point::getX() const { 
    return x_; 
}

double Point::getY() const { 
    return y_; 
}

void Point::setX(double x) {
    assert(!std::isnan(x));
    x_ = x;
}

void Point::setY(double y) {
    assert(!std::isnan(y));
    y_ = y;
}

double Point::distance(const Point& other) const {
    double dx = x_ - other.x_;
    double dy = y_ - other.y_;
    return std::sqrt(dx * dx + dy * dy);
}

Point Point::operator+(const Point& other) const {
    return Point(x_ + other.x_, y_ + other.y_);
}

Point Point::operator-(const Point& other) const {
    return Point(x_ - other.x_, y_ - other.y_);
}

Point& Point::operator+=(const Point& other) {
    x_ += other.x_;
    y_ += other.y_;
    return *this;
}

Point& Point::operator-=(const Point& other) {
    x_ -= other.x_;
    y_ -= other.y_;
    return *this;
}

bool Point::operator==(const Point& other) const {
    const double eps = 1e-7;
    return std::abs(x_ - other.x_) < eps && std::abs(y_ - other.y_) < eps;
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

std::istream& operator>>(std::istream& in, Point& p) {
    in >> p.x_ >> p.y_;
    if (in.fail()) {
        throw std::invalid_argument("Invalid input for Point");
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Point& p) {
    out << "(" << p.x_ << ", " << p.y_ << ")";
    return out;
}