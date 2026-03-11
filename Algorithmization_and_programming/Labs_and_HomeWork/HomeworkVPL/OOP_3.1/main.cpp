#include "ShapeCollection.h"
#include "Shape.h"
#include <iostream>

void test_1() {
    std::cout << "Test 1: Basic shapes" << std::endl;
    Circle c(5);
    Rectangle r(3, 4);
    std::cout << "Circle area: " << c.area() << std::endl;
    std::cout << "Rectangle area: " << r.area() << std::endl;
}

void test_2() {
    std::cout << "\nTest 2: Collection operations" << std::endl;
    ShapeCollection coll;
    coll + new Circle(2);
    coll + new Rectangle(3, 4);
    coll + new Circle(1);
    
    std::cout << "Collection has " << coll.getCurrentFigures() << " figures" << std::endl;
    coll.printAreas();
}

void test_3() {
    std::cout << "\nTest 3: Find smallest area" << std::endl;
    ShapeCollection coll;
    coll + new Circle(10);
    coll + new Rectangle(1, 1); 
    coll + new Circle(5);    
    
    const Shape* smallest = coll.findSmallestArea();
    if (smallest) {
        std::cout << "Smallest area figure: " << smallest->name() 
                  << " with area " << smallest->area() << std::endl;
    }
}

void test_4() {
    std::cout << "\nTest 4: Count shapes by name" << std::endl;
    ShapeCollection coll;
    coll + new Circle(1);
    coll + new Rectangle(2, 3);
    coll + new Circle(2);
    coll + new Rectangle(1, 1);
    
    std::cout << "Circles: " << coll.getNumberRepetitionsName("Circle") << std::endl;
    std::cout << "Rectangles: " << coll.getNumberRepetitionsName("Rectangle") << std::endl;
}

void test_5() {
    std::cout << "\nTest 5: Copy collection" << std::endl;
    ShapeCollection coll1;
    coll1 + new Circle(3);
    coll1 + new Rectangle(2, 5);
    
    ShapeCollection coll2 = coll1;
    std::cout << "Original size: " << coll1.getCurrentFigures() << std::endl;
    std::cout << "Copy size: " << coll2.getCurrentFigures() << std::endl;
}

void test_6() {
    std::cout << "\nTest 6: Output all figures" << std::endl;
    ShapeCollection coll;
    coll + new Circle(-4);
    coll + new Rectangle(5, 6);
    
    std::cout << coll;
}

int main() {
    try {
        test_1();
        test_2();
        test_3();
        test_4();
        test_5();
        test_6();
        std::cout << "\nAll tests passed!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}