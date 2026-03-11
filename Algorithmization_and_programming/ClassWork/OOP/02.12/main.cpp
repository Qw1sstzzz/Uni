#include "Shape.h"
#include <iostream>

int main() {
    Circle circle(5);
    Rectangle rectangle(3, 4);

    Shape* p1 = &circle;
    Shape* p2 = &rectangle;

    std::cout << p1->name() << " area: " << p1->area() << " ; perimeter: " << p1->perimeter() << "\n";
    std::cout << p2->name() << " area: " << p2->area() << " ; perimeter: " << p2->perimeter() << "\n";
    std::cout << rectangle.aspectRatio() << std::endl;
    return 0;
}