#include "Point_copy.h"

#include <iostream>

int main(void) {
    Point point;
    input(point);
    std::cout << point.getX() << " " << point.getY() << std::endl;
    std::cout << isPointInCircle(point, 5) << std::endl;
    point.setX(3.0).setY(4.0).move(1.0);
    output(point);
    return 0;
}