#include "Point.h"
#include "Triangle.h"

#include <iostream>
#include <stdexcept>

int main(void) {
    try {
        Triangle triangle1, triangle2;
        
        std::cout << "Enter the first triangle (Triangle1):\n";

        std::cin >> triangle1;
        if (std::cin.fail()) {
            throw std::invalid_argument("Wrong input!!!");
        }
        if (!triangle1.isTriangle()) {
            throw std::runtime_error("ERROR: it is impossible to construct a triangle from given points for triangle №1");
        }
        
        std::cout << "Enter the second triangle (Triangle2):\n";
        std::cin >> triangle2;
        if (std::cin.fail()) {
            throw std::invalid_argument("Wrong input!!!");
        }
        if (!triangle2.isTriangle()) {
            throw std::runtime_error("ERROR: it is impossible to construct a triangle from given points for triangle №2");
        }

        std::cout.precision(4);
        
        if (triangle1 == triangle2) {
            std::cout << "The triangles are equal:)\n";
        } 
        else {
            std::cout << "The triangles are not equal:(\n";
        }
        
        if (triangle1 < triangle2) {
            std::cout << "The area of the first triangle is less than the second\n";
        } 
        else {
            std::cout << "The area of the first triangle is NOT less than the second\n";
        }
        
        int K;
        std::cout << "Enter K for moving Triangle1: ";
        std::cin >> K;
        
        if (std::cin.fail()) {
            throw std::invalid_argument("ERROR: invalid input for K");
        }
        
        triangle1 += K;
        
        std::cout << "Triangle1 moved, new vertices:\n" << triangle1 << std::endl;
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
