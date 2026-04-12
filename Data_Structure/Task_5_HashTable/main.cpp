#include "HashTable.h"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        std::cout << "--- Testing basic operations ---\n";
        HashTable ht(10);

        ht.insert(3.14, 9.8);
        ht.insert(2.71, 7.3);
        ht.insert(1.41, 1.0);

        std::cout << "Table after inserts:\n";
        ht.print();

        std::cout << "\n--- Testing find ---\n";
        std::cout << "Find 3.14: " << (ht.find(3.14) != -1 ? "found" : "not found") << '\n';
        std::cout << "Find 99.9: " << (ht.find(99.9) != -1 ? "found" : "not found") << '\n';

        std::cout << "\n--- Testing remove ---\n";
        ht.remove(2.71);
        std::cout << "After removing 2.71:\n";
        ht.print();

        std::cout << "\n--- Testing insert after delete ---\n";
        ht.insert(5.55, 55.5);
        ht.print();

        std::cout << "\n--- Testing collisions ---\n";
        std::cout << "Collisions: " << ht.getCollisions() << '\n';

        std::cout << "\n--- Testing duplicate ---\n";
        ht.insert(3.14, 999.0);
        std::cout << "After duplicate insert attempt (value should not change):\n";
        ht.print();

        std::cout << "\n--- Testing load factor limit ---\n";
        HashTable small(4);
        small.insert(0.1, 1.0);
        small.insert(0.2, 2.0);
        small.insert(0.3, 3.0);
        small.insert(0.4, 4.0);
        std::cout << "Small table (size 4, should have only 2-3 elements):\n";
        small.print();

        std::cout << "\n--- Testing negative keys ---\n";
        HashTable neg(8);
        neg.insert(-1.5, -10.0);
        neg.insert(-2.5, -20.0);
        std::cout << "Find -1.5: " << (neg.find(-1.5) != -1 ? "found" : "not found") << '\n';
        std::cout << "Find -99.0: " << (neg.find(-99.0) != -1 ? "found" : "not found") << '\n';

        std::cout << "\n--- Testing edge cases ---\n";

        std::cout << "Removing non-existent key... ";
        ht.remove(123.456);
        std::cout << "OK (no crash)\n";

        std::cout << "Creating empty table... ";
        HashTable empty(5);
        std::cout << "Find in empty: " << (empty.find(1.0) != -1 ? "found" : "not found") << '\n';

        std::cout << "\n--- All tests passed ---\n";

    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "UNKNOWN ERROR\n";
        return 1;
    }

    return 0;
}
