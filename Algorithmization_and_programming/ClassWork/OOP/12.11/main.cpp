#include "Point.h"
#include "Triangle.h"

#include <iostream>
#include <stdexcept>

int main(void) {
    try {
        std::cout << "Enter coordinates for triangleR (ax ay bx by cx cy):\n";
        double ax, ay, bx, by, cx, cy;
        std::cin >> ax >> ay >> bx >> by >> cx >> cy;
        
        if (std::cin.fail()) {
            throw std::invalid_argument("ERROR: invalid input for triangleR coordinates");
        }
        
        Triangle triangleR(ax, ay, bx, by, cx, cy);
        
        if (!triangleR.isTriangle()) {
            throw std::runtime_error("ERROR: it is impossible to construct a triangle from given points for triangleR");
        }
        
        std::cout.precision(2);
        std::cout << "perimeterR: " << std::fixed << triangleR.getPerimeter() << std::endl;
        
        std::cout << "Enter coordinates for triangleP (ax ay bx by cx cy):\n";
        std::cin >> ax >> ay >> bx >> by >> cx >> cy;
        
        if (std::cin.fail()) {
            throw std::invalid_argument("ERROR: invalid input for triangleP coordinates");
        }
        
        Triangle triangleP(ax, ay, bx, by, cx, cy);
        
        if (!triangleP.isTriangle()) {
            throw std::runtime_error("ERROR: it is impossible to construct a triangle from given points for triangleP");
        }
        
        std::cout << "perimeterP: " << std::fixed << triangleP.getPerimeter() << std::endl;
        
        if (triangleR.isEqual(triangleP)) {
            std::cout << "The triangles are equal:)\n";
        } 
        else {
            std::cout << "The triangles are not equal:(\n";
        }
        
        if (isEqualSquare(triangleR, triangleP)) {
            std::cout << "The areas are equal;)\n";
        } 
        else {
            std::cout << "The areas are not equal;(\n";
        }
        
        int K;
        std::cout << "Enter K for moving triangleP: ";
        std::cin >> K;
        
        if (std::cin.fail()) {
            throw std::invalid_argument("ERROR: invalid input for K");
        }
        
        triangleP.move(K);
        
        std::cout << "TriangleP moved, new vertices : \n";
        output(triangleP);
        
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    catch (...) {
        std::cerr << "ERROR: unknown exception occurred" << std::endl;
        return 1;
    }
    
    return 0;
}