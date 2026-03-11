#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"
#include <iostream>
#include <cmath>
#include <cassert>


class Triangle {
private:
    Point a_, b_, c_;

public:
    Triangle() : a_(0, 0), b_(0, 1), c_(1, 0) {};

    Triangle(double ax, double ay, double bx, double by, double cx, double cy) : a_(ax, ay), b_(bx, by), c_(cx, cy) {
    } ;

    ~Triangle() {};


    void setA(double x, double y);
    void setB(double x, double y);
    void setC(double x, double y);

    Point getA() const;
    Point getB() const;
    Point getC() const;

    bool isTriangle() const;
    void move(int k);
    double getPerimeter() const;
    double getSquare() const;
    bool isEqual(const Triangle& other) const;
};

bool isEqualSquare(const Triangle& t1, const Triangle& t2);

void output(const Triangle& t);

#endif