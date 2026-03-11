#include "Shape.h"

void Circle::print(std::ostream& out) const {
    out << "Figure: " << name() 
        << "\nRadius: " << radius_
        << "\nArea: " << area()
        << "\nPerimeter: " << perimeter() << std::endl;
}


void Rectangle::print(std::ostream& out) const {
    out << "Figure: " << name() 
        << "\nWidth: " << width_
        << "\nHeight: " << height_
        << "\nArea: " << area()
        << "\nPerimeter: " << perimeter()
        << "\nAspect Ratio: " << aspectRatio() << std::endl;
}


std::ostream& operator<<(std::ostream& out, const Shape* shape) {
    if (shape != nullptr) {
        shape->print(out);
    } 
    else {
        out << "Shape pointer: nullptr\n";
    }
    return out;
}