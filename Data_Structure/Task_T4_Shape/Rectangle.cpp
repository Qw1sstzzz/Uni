#include <iostream>
#include <string>
#include "Rectangle.h"

Rectangle::Rectangle(const Point& bl, const Point& tr) : bottomLeft(bl), topRight(tr) {}

double Rectangle::getArea() const {
    double width = topRight.x - bottomLeft.x;
    double height = topRight.y - bottomLeft.y;
    return width * height;
}

Point Rectangle::getCenter() const {
    double centerX = (topRight.x + bottomLeft.x) / 2.0;
    double centerY = (topRight.y + bottomLeft.y) / 2.0;
    return Point(centerX, centerY);
}

void Rectangle::move(double dx, double dy) {
    bottomLeft.x += dx;
    bottomLeft.y += dy;

    topRight.x += dx;
    topRight.y += dy;
}

void Rectangle::scale(double fact) {
    Point center = getCenter();
    bottomLeft.x = center.x + (bottomLeft.x - center.x) * fact;
    bottomLeft.y = center.y + (bottomLeft.y - center.y) * fact;

    topRight.x = center.x + (topRight.x - center.x) * fact;
    topRight.y = center.y + (topRight.y - center.y) * fact;
}

std::string Rectangle::getName() const {
    return "RECTANGLE";
}
