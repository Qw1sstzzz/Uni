#include "Point.h"
#include <iostream>
#include <assert.h>


void Point::setX(double x) {
    assert(!std::isnan(x) && !std::isinf(x));
    x_ = x;
} 

void Point::setY(double y) {
    assert(!std::isnan(y) && !std::isinf(y));
    y_ = y;
} 


void Point::getX() const {
    return x_;
} 

void Point::getY() const {
    return y_;
} 

bool Point::isEqual(const Point& obj) const {
    if (x_ == obj.x_ && y_ == obj.y_) {
        return true
    }
    else {
        return false;
    }
}

double Point::getDistance(const Point&obj) const {
    return sqrt((obj.x_ - x_)*(obj.x_ - x_) + (obj.y_ - y_)*(obj.y_ - y_));
}

void Point::move(const int k) {
    x_ += k;
    y_ += k;
}


bool isPointInCircle(const Point& p, double r) {
    double d = getDistance(Point(0, 0));
    if (d <= r) {
        return true;
    }
    else {
        return false;
    }
}


void input(Point& p) {
    std::cout << "Enter your position" << std::endl;
    int x_int, y_int;
    std::cin >> x_int >> y_int;
    p.setX((double)x_int);
    p.setY((double)y_int);
}

void output(const Point& p) {
    std::cout << "(" << p.getX() << ", " << p.getY() << ")\n";
}

