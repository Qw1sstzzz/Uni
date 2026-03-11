#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cassert>
#include <cmath>


class Point {
public:
    // Конструктор по умолчанию:
    Point() : x_(0.0), y_(0.0) {}

    // Конструктор с параметрами:
    Point(double x0, double y0) : x_(x0), y_(y0) {
        assert(!std::isnan(x_) && !std::isinf(x_));
        assert(!std::isnan(y_) && !std::isinf(y_));
    } ;

    // Конструктор копирования:
    Point(const Point& object) : x_(object.x_), y_(object.y_) {};

    // Деструктор
    ~Point() {};

    Point& setX(const double x);
    Point& setY(const double y);

    double getX() const;
    double getY() const;

    bool isEqual(const Point& object) const;
    double getDistance(const Point& object) const;
    Point& move(const int k);

private:
    // Закрытые данные (поля)
    double x_{ 0.0 };   // Координата x
    double y_{ 0.0 };   // Координата y
} ;

bool isPointInCircle(const Point& p, double r);
void input(Point& p);
void output(const Point& p);

#endif