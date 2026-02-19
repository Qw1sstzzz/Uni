#include <iostream>
#include <cstdlib>
#include <cstddef>

static size_t total_allocated = 0;  

void* operator new(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        throw std::bad_alloc();
    }

    total_allocated += size;
    
    std::cout << "+ " << size << " bytes (total = " << total_allocated << ")\n";
    
    return ptr; 
}
 
void* operator new[](size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        throw std::bad_alloc();
    }

    total_allocated += size;
    
    std::cout << "+ " << size << " bytes (array, total = " << total_allocated << ")\n";
    
    return ptr; 
}

void operator delete(void* ptr) noexcept {
    if (ptr) {
        std::cout << "- memory freed\n";
        free(ptr);
    }
}

void operator delete[](void* ptr) noexcept {
    if (ptr) {
        std::cout << "- array memory freed\n";
        free(ptr);
    }
}

void testMemory() {
    std::cout << "Test 1 : variables \n";
    int* p1 = new int(5);
    double* p2 = new double(3.14); 
    delete p1;
    
    std::cout << "\nTest 2 : array \n";
    int* array = new int[10];
    delete[] array;
    
    std::cout << "\nTest 3 : several objects \n";
    for (int i = 0; i < 3; i++) {
        char* c = new char('A' + i);
        if (i % 2 == 0) {
            delete c;
            std::cout << "  Deleted char " << char('A' + i) << "\n";
        } 
        else {
            std::cout << "  Leaked char " << char('A' + i) << "\n";
        }
    }
}

int main() {
    std::cout << "Memory test\n\n";
    testMemory();
    
    std::cout << "\nFinal state:\n";
    std::cout << "Total allocated: " << total_allocated << " bytes\n";
    
    return 0;
}