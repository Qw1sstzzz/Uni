#include "Polynomial.h"
#include "Polygon.h"
#include <iostream>

int main() {
    try {
        std::cout << "=== Simple Test ===" << std::endl;
        
        // Test Point
        Point p1(1, 2);
        Point p2(3, 4);
        std::cout << "Point test: " << p1 << " + " << p2 << " = " << (p1 + p2) << std::endl;
        
        // Test Polygon
        Point points[] = {Point(0, 0), Point(1, 0), Point(1, 1)};
        Polygon tri(points, 3);
        std::cout << "Triangle perimeter: " << tri.perimeter() << std::endl;
        
        // Test Polynomial
        double coeffs[] = {1, 2, 3}; // 1 + 2x + 3x^2
        Polynomial poly(coeffs, 2);
        std::cout << "Polynomial at x=2: " << poly.evaluate(2) << std::endl;
        
        std::cout << "\n=== All tests completed successfully! ===" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

/* 
Как запустить код^

1) Перешёл в папку через терминал VSCode'a (Ctrl + `)
2) Ввёл                     g++ -std=c++11 -g main.cpp Point.cpp Polygon.cpp Polynomial.cpp -o main.exe
3) Ввести                   .\main.exe
*/ 