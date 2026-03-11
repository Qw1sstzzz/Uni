#include "Triangle.h"
#include "Point.h"

#include <iostream>
#include <cmath>
const double eps = 1e-5;

void Triangle::setA(double x, double y) { 
    a_ = Point(x, y); 
}
void Triangle::setB(double x, double y) { 
    b_ = Point(x, y); 
}
void Triangle::setC(double x, double y) { 
    c_ = Point(x, y); 
}

Point Triangle::getA() const { 
    return a_; 
}
Point Triangle::getB() const { 
    return b_; 
}
Point Triangle::getC() const { 
    return c_; 
}

bool Triangle::isTriangle() const {
    double ab = a_.getDistance(b_);
    double bc = b_.getDistance(c_);
    double ca = c_.getDistance(a_);
    
    
    if (((ab + bc < ca + eps) || (ab + ca < bc + eps) || (ca + bc < ab + eps)) || ((ab < eps) || (bc < eps) || (ca < eps))) {
        return false;
    }
    else {
        return true;
    }
}

void Triangle::move(int k) {
    a_.move(k);
    b_.move(k);
    c_.move(k);
}

double Triangle::getPerimeter() const {
    if (!isTriangle()) {
        return 0.0;
    }
    
    double ab = a_.getDistance(b_);
    double bc = b_.getDistance(c_);
    double ca = c_.getDistance(a_);
    
    return ab + bc + ca;
}

double Triangle::getSquare() const {
    if (!isTriangle()) {
        return 0.0;
    }
    
    double ab = a_.getDistance(b_);
    double bc = b_.getDistance(c_);
    double ca = c_.getDistance(a_);
    double p = (ab + bc + ca) / 2.0;
    
    return sqrt(p * (p - ab) * (p - bc) * (p - ca));
}


Triangle& Triangle::operator+=(int k) {
    a_ += k;
    b_ += k;
    c_ += k;
    return *this;
}

bool Triangle::operator==(const Triangle& t) const {
    return ((a_ == t.a_) && (b_ == t.b_) && (c_ == t.c_));
}

bool Triangle::operator<(const Triangle& t) const {
    return this->getSquare() < t.getSquare();
}

std::ostream& operator<<(std::ostream& os, const Triangle& t) {
    os << t.a_ << " " << t.b_ << " " << t.c_;
    return os;
}


std::istream& operator>>(std::istream& is, Triangle& t) {
    is >> t.a_ >> t.b_ >> t.c_;
    return is;
}