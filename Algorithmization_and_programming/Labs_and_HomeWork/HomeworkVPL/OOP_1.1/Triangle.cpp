#include "Triangle.h"
#include "Point.h"

#include <iostream>
#include <cmath>


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
    const double eps = 1e-5;
    double ab = a_.getDistance(b_);
    double bc = b_.getDistance(c_);
    double ca = c_.getDistance(a_);
    
    if ((ab + bc < ca + eps) || (ab + ca < bc + eps) || (ca + bc < ab + eps)) {
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

bool Triangle::isEqual(const Triangle& other) const {
    return (a_.isEqual(other.a_) && (b_.isEqual(other.b_)) && (c_.isEqual(other.c_)));
}

bool isEqualSquare(const Triangle& t1, const Triangle& t2) {
    double area1 = t1.getSquare();
    double area2 = t2.getSquare();
    
    return (std::abs(area1 - area2) < 1e-5);
}

void output(const Triangle& t) {
    std::cout << "Triangle vertices: ";
    output(t.getA());
    std::cout << " ";
    output(t.getB());
    std::cout << " ";
    output(t.getC());
}