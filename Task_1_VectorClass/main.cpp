#include "Vector.h"
#include <iostream>
#include <string>

void testConstructors() {
    std::cout << "\n=== Constructors Test ===\n";
    
    try {
        Vector<int> v1;
        std::cout << "Default constructor: size = " << v1.size() << ", capacity = " << v1.capacity() << std::endl;
        
        Vector<int> v2(5);
        std::cout << "Vector(5): size = " << v2.size() << ", capacity = " << v2.capacity() << std::endl;
        std::cout << "Elements: ";
        for (size_t i = 0; i < v2.size(); i++) std::cout << v2[i] << " ";
        std::cout << std::endl;
        
        Vector<int> v3(5, 42);
        std::cout << "Vector(5, 42): first = " << v3[0] << ", last = " << v3[4] << std::endl;
        
        Vector<int> v4(v3);
        std::cout << "Copy constructor: size = " << v4.size() << ", first = " << v4[0] << std::endl;
        
        Vector<int> v5(std::move(v4));
        std::cout << "Move constructor: size = " << v5.size() << ", first = " << v5[0] << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in testConstructors: " << e.what() << std::endl;
    }
}

void testAccess() {
    std::cout << "\n=== Access Methods Test ===\n";
    
    try {
        Vector<int> v;
        for (int i = 0; i < 5; i++) v.push_back(i * 10);
        
        std::cout << "Elements: ";
        for (size_t i = 0; i < v.size(); i++) std::cout << v[i] << " ";
        std::cout << std::endl;
        
        std::cout << "front() = " << v.front() << ", back() = " << v.back() << std::endl;
        std::cout << "at(2) = " << v.at(2) << std::endl;
        std::cout << "operator[3] = " << v[3] << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in testAccess: " << e.what() << std::endl;
    }
}

void testPushBack() {
    std::cout << "\n=== Push_back Test ===\n";
    
    try {
        Vector<int> v;
        std::cout << "Initial: size = " << v.size() << ", capacity = " << v.capacity() << std::endl;
        
        for (int i = 1; i <= 5; i++) {
            v.push_back(i * 10);
            std::cout << "After push " << i*10 << ": size = " << v.size() << ", capacity = " << v.capacity() << std::endl;
        }
        
        std::cout << "Final elements: ";
        for (size_t i = 0; i < v.size(); i++) std::cout << v[i] << " ";
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in testPushBack: " << e.what() << std::endl;
    }
}

void testPopBackAndClear() {
    std::cout << "\n=== Pop_back and Clear Test ===\n";
    
    try {
        Vector<std::string> v;
        v.push_back("one");
        v.push_back("two");
        v.push_back("three");
        
        std::cout << "Before pop: size = " << v.size() << ", elements: ";
        for (size_t i = 0; i < v.size(); i++) std::cout << v[i] << " ";
        std::cout << std::endl;
        
        v.pop_back();
        std::cout << "After pop: size = " << v.size() << ", elements: ";
        for (size_t i = 0; i < v.size(); i++) std::cout << v[i] << " ";
        std::cout << std::endl;
        
        v.clear();
        std::cout << "After clear: size = " << v.size() << ", capacity = " << v.capacity() << std::endl;
        
        v.pop_back(); 
        std::cout << "pop_back on empty: size = " << v.size() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in testPopBackAndClear: " << e.what() << std::endl;
    }
}

void testInsertAndErase() {
    std::cout << "\n=== Insert and Erase Test ===\n";
    
    try {
        Vector<int> v;
        for (int i = 1; i <= 3; i++) v.push_back(i);
        std::cout << "Initial: ";
        for (size_t i = 0; i < v.size(); i++) std::cout << v[i] << " ";
        std::cout << std::endl;
        
        v.insert(1, 10);
        std::cout << "After insert(1, 10): ";
        for (size_t i = 0; i < v.size(); i++) std::cout << v[i] << " ";
        std::cout << std::endl;
        
        v.erase(2);
        std::cout << "After erase(2): ";
        for (size_t i = 0; i < v.size(); i++) std::cout << v[i] << " ";
        std::cout << std::endl;
        
        v.erase(1, 2);
        std::cout << "After erase(1, 2): ";
        for (size_t i = 0; i < v.size(); i++) std::cout << v[i] << " ";
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in testInsertAndErase: " << e.what() << std::endl;
    }
}

void testReserveAndResize() {
    std::cout << "\n=== Reserve and Resize Test ===\n";
    
    try {
        Vector<int> v;
        v.reserve(10);
        std::cout << "After reserve(10): size = " << v.size() << ", capacity = " << v.capacity() << std::endl;
        
        v.resize(5, 100);
        std::cout << "After resize(5, 100): ";
        for (size_t i = 0; i < v.size(); i++) std::cout << v[i] << " ";
        std::cout << std::endl;
        
        v.resize(3);
        std::cout << "After resize(3): ";
        for (size_t i = 0; i < v.size(); i++) std::cout << v[i] << " ";
        std::cout << std::endl;
        
        v.shrink_to_fit();
        std::cout << "After Shrink_to_fit: size = " << v.size() << ", capacity = " << v.capacity() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in testReserveAndResize: " << e.what() << std::endl;
    }
}

void testComparators() {
    std::cout << "\n=== Comparison Operators Test ===\n";
    
    try {
        Vector<int> v1;
        v1.push_back(1);
        v1.push_back(2);
        v1.push_back(3);
        
        Vector<int> v2;
        v2.push_back(1);
        v2.push_back(2);
        v2.push_back(3);
        
        Vector<int> v3;
        v3.push_back(1);
        v3.push_back(2);
        v3.push_back(4);
        
        std::cout << "v1 == v2: " << (v1 == v2 ? "true" : "false") << std::endl;
        std::cout << "v1 != v3: " << (v1 != v3 ? "true" : "false") << std::endl;
        std::cout << "v1 < v3: " << (v1 < v3 ? "true" : "false") << std::endl;
        std::cout << "v3 > v1: " << (v3 > v1 ? "true" : "false") << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in testComparators: " << e.what() << std::endl;
    }
}

void testSort() {
    std::cout << "\n=== Insertion Sort Test ===\n";
    
    try {
        Vector<int> v;
        v.push_back(5);
        v.push_back(2);
        v.push_back(8);
        v.push_back(1);
        v.push_back(9);
        v.push_back(3);
        
        std::cout << "Before sorting: ";
        for (size_t i = 0; i < v.size(); i++) std::cout << v[i] << " ";
        std::cout << std::endl;
        
        insertionSort(v);
        
        std::cout << "After sorting:  ";
        for (size_t i = 0; i < v.size(); i++) std::cout << v[i] << " ";
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in testSort: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "=== VECTOR CLASS TESTS ===" << std::endl;
    
    testConstructors();
    testAccess();
    testPushBack();
    testPopBackAndClear();
    testInsertAndErase();
    testReserveAndResize();
    testComparators();
    testSort();
    
    std::cout << "\n=== All tests completed successfully ===" << std::endl;
    return 0;
}