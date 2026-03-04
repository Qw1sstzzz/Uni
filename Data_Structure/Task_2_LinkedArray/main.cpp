#include "singly_ordered_list.h"

#include <iostream>
#include <string>


int main() {
    std::cout << "========== TESTING SINGLY ORDERED LIST ==========\n\n";

    std::cout << "--- Constructor Tests ---\n";
    
    SinglyOrderedList<int> list1;
    std::cout << "Default constructor: list is " << (list1.isEmpty() ? "empty" : "not empty") << ", size = " << list1.size() << "\n";
    
    SinglyOrderedList<int> list2(42);
    std::cout << "Constructor with value 42: size = " << list2.size() << ", head = " << list2.head() << "\n";
    
    SinglyOrderedList<int> list3(list2);
    std::cout << "Copy constructor: size = " << list3.size() << ", head = " << list3.head() << "\n";
    
    SinglyOrderedList<int> list4(std::move(list3));
    std::cout << "Move constructor: list4 size = " << list4.size() << ", list4 head = " << list4.head() << ", list3 is " << (list3.isEmpty() ? "empty" : "not empty") << "\n\n";

    std::cout << "--- Insert Tests ---\n";
    
    SinglyOrderedList<int> list5;
    list5.insert(30);
    list5.insert(10);
    list5.insert(20);
    list5.insert(40);
    
    std::cout << "After inserting 30, 10, 20, 40: ";
    list5.print();
    std::cout << "Size = " << list5.size() << ", head = " << list5.head() << ", tail = " << list5.tail() << "\n\n";

    std::cout << "--- Search Tests ---\n";
    std::cout << "Search for 20: " << (list5.search(20) ? "found" : "not found") << "\n";
    std::cout << "Search for 99: " << (list5.search(99) ? "found" : "not found") << "\n\n";

    std::cout << "--- Head/Tail Tests ---\n";
    std::cout << "head() returns: " << list5.head() << "\n";
    std::cout << "tail() returns: " << list5.tail() << "\n\n";

    std::cout << "--- Remove Tests ---\n";
    
    SinglyOrderedList<int> list6;
    list6.insert(10);
    list6.insert(20);
    list6.insert(30);
    
    list6.removeHead();
    std::cout << "After removeHead(): size = " << list6.size() << ", head = " << list6.head() << "\n";
    
    bool removed = list6.removeKey(30);
    std::cout << "removeKey(30): " << (removed ? "removed" : "not found") << ", size = " << list6.size() << ", tail = " << list6.tail() << "\n";
    
    removed = list6.removeKey(99);
    std::cout << "removeKey(99): " << (removed ? "removed" : "not found") << ", size = " << list6.size() << "\n";
    
    SinglyOrderedList<int> list7;
    try {
        list7.removeHead();
        std::cout << "removeHead on empty: should not see this\n";
    } catch (const std::runtime_error& e) {
        std::cout << "removeHead on empty: caught exception: " << e.what() << "\n";
    }
    
    std::cout << "\n--- Clear Tests ---\n";
    
    SinglyOrderedList<int> list8;
    list8.insert(1);
    list8.insert(2);
    list8.insert(3);
    list8.clear();
    std::cout << "After clear(): list is " << (list8.isEmpty() ? "empty" : "not empty") << ", size = " << list8.size() << "\n\n";
    
    std::cout << "--- Comparison Operator Tests ---\n";
    
    SinglyOrderedList<int> list9, list10;
    list9.insert(1); list9.insert(2); list9.insert(3);
    list10.insert(1); list10.insert(2); list10.insert(3);
    
    std::cout << "list9 == list10: " << ((list9 == list10) ? "true" : "false") << "\n";
    
    SinglyOrderedList<int> list11;
    list11.insert(1); list11.insert(2); list11.insert(4);
    std::cout << "list9 == list11: " << ((list9 == list11) ? "true" : "false") << "\n\n";

    std::cout << "--- Intersection Tests ---\n";
    
    SinglyOrderedList<int> listA, listB;
    listA.insert(1); listA.insert(2); listA.insert(3); listA.insert(4);
    listB.insert(3); listB.insert(4); listB.insert(5); listB.insert(6);
    
    SinglyOrderedList<int> intersection = getIntersection(listA, listB);
    std::cout << "Intersection of A and B: ";
    intersection.print();  
    
    std::cout << "Intersection size = " << intersection.size() << ", contains 3: " << (intersection.search(3) ? "yes" : "no") << ", contains 4: " << (intersection.search(4) ? "yes" : "no") << "\n\n";
    
    std::cout << "--- Remove List Tests ---\n";
    
    SinglyOrderedList<int> listC, listD;
    listC.insert(1); listC.insert(2); listC.insert(3); listC.insert(4); listC.insert(5);
    listD.insert(2); listD.insert(4);
    
    listC.remove(listD);
    std::cout << "List C after removing elements of D: ";
    listC.print();  
    
    std::cout << "Size = " << listC.size() << ", head = " << listC.head() << ", tail = " << listC.tail() << ", contains 2: " << (listC.search(2) ? "yes" : "no") << ", contains 4: " << (listC.search(4) ? "yes" : "no") << "\n\n";
    
    std::cout << "--- String Type Tests ---\n";
    
    SinglyOrderedList<std::string> listStr;
    listStr.insert("banana");
    listStr.insert("apple");
    listStr.insert("cherry");
    
    std::cout << "String list (sorted): ";
    listStr.print(); 
    
    std::cout << "head = " << listStr.head() << ", tail = " << listStr.tail() << "\n";
    
    std::cout << "\n========== ALL TESTS COMPLETED ==========\n";
    
    return 0;
}