// Variant - 1


#include "Vector3D.h"
#include <iostream>

void test_constructors() {
    std::cout << "=== Testing constructors ===" << std::endl;
    
    Vector3D v1;
    std::cout << "Default: " << v1 << std::endl;
    
    Vector3D v2(1.0, 2.0, 3.0);
    std::cout << "With parametres: " << v2 << std::endl;
    std::cout << "Length: " << v2.length() << std::endl;
    
    Vector3D v3(v2);
    std::cout << "Copy: " << v3 << std::endl;
    
    Vector3D v4(std::move(v2));
    std::cout << "Move: " << v4 << std::endl;
}

void test_assignment() {
    std::cout << "\n=== Testing assignment ===" << std::endl;
    
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2;
    
    v2 = v1;
    std::cout << "Copy assignment: " << v2 << std::endl;
    
    Vector3D v3;
    v3 = std::move(v1);
    std::cout << "Move assignment: " << v3 << std::endl;
}

void test_operations() {
    std::cout << "\n=== Testing operations ===" << std::endl;
    
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);
    
    Vector3D sum = v1 + v2;
    std::cout << v1 << " + " << v2 << " = " << sum << std::endl;
    
    Vector3D v3(1.0, 2.0, 3.0);
    std::cout << v1 << " == " << v3 << ": " << (v1 == v3 ? "yes" : "no") << std::endl;
    std::cout << v1 << " == " << v2 << ": " << (v1 == v2 ? "yes" : "no") << std::endl;
}

void test_getters_setters() {
    std::cout << "\n=== Testing getters/setters ===" << std::endl;
    
    Vector3D v;
    v.setX(10.0);
    v.setY(20.0);
    v.setZ(30.0);
    
    std::cout << "After setters: " << v << std::endl;
    std::cout << "getX(): " << v.getX() << std::endl;
    std::cout << "getY(): " << v.getY() << std::endl;
    std::cout << "getZ(): " << v.getZ() << std::endl;
}

void test_self_assignment() {
    std::cout << "\n=== Testing self-assignment ===" << std::endl;
    
    Vector3D v1(5.0, 6.0, 7.0);
    std::cout << "Before self-assignment: " << v1 << std::endl;
    
    v1 = v1;
    std::cout << "After self-assignment: " << v1 << std::endl;
}

int main() {
    try {
        test_constructors();
        test_assignment();
        test_operations();
        test_getters_setters();
        test_self_assignment();
        
        std::cout << "\nAll tests passed!" << std::endl;
        return 0;
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } 
    catch (const std::bad_alloc& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } 
    catch (const std::exception& e) {
        std::cerr << "Something went wrong..." << e.what() << std::endl;
        return 1;
    }
}