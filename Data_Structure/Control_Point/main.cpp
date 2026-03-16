#include "SinglyLinkedArray.h"
#include <iostream>

void test1() {
    std::cout << "\n=== Базовый тест ===" << std::endl;
    try {
        SinglyLinkedArray list;
        std::cout << "Создан пустой список" << std::endl;
        std::cout << "isEmpty(): " << (list.isEmpty() ? "Да" : "Нет") << std::endl;
        std::cout << "size: " << list.size() << std::endl;
        
        if (list.isEmpty() && list.size() == 0) {
            std::cout << "✓ Конструктор создает пустой список" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "✗ Ошибка: " << e.what() << std::endl;
    }
}

void test2() {
    std::cout << "\n=== Insert и removeMax тест ===" << std::endl;
    try {
        SinglyLinkedArray list;
        list.insert(10);
        list.insert(20);
        list.insert(50);
        list.insert(30);
        list.insert(50);
        list.insert(15);
        
        std::cout << "Исходный список: ";
        list.print();
        std::cout << "size: " << list.size() << std::endl;
        
        list.removeMax(); // Должен удалить все 50
        std::cout << "После removeMax(): ";
        list.print();
        std::cout << "size: " << list.size() << std::endl;
        
        list.deleteLess(25);
        std::cout << "После deleteLess(25): ";
        list.print();
        std::cout << "size: " << list.size() << std::endl;
        
        std::cout << "Очистка списка..." << std::endl;
        list.clear();
        std::cout << "После clear(): size = " << list.size() << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "✗ Ошибка: " << e.what() << std::endl;
    }
}

void test3() {
    std::cout << "\n=== Тест move операций ===" << std::endl;
    try {
        SinglyLinkedArray list1;
        list1.insert(1);
        list1.insert(2);
        list1.insert(3);
        
        std::cout << "list1: ";
        list1.print();
        
        // Тест move конструктора
        SinglyLinkedArray list2 = std::move(list1);
        std::cout << "После move в list2:" << std::endl;
        std::cout << "  list2: ";
        list2.print();
        std::cout << "  list1 пуст? " << (list1.isEmpty() ? "Да" : "Нет") << std::endl;
        
        // Тест move присваивания
        SinglyLinkedArray list3;
        list3.insert(100);
        std::cout << "list3 до присваивания: ";
        list3.print();
        
        list3 = std::move(list2);
        std::cout << "list3 после присваивания: ";
        list3.print();
        std::cout << "list2 пуст? " << (list2.isEmpty() ? "Да" : "Нет") << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "✗ Ошибка: " << e.what() << std::endl;
    }
}

void test4() {
    std::cout << "\n=== Граничные случаи ===" << std::endl;
    try {
        SinglyLinkedArray list;
        
        // removeMax на пустом списке
        std::cout << "removeMax на пустом списке:" << std::endl;
        list.removeMax();
        
        // deleteLess на пустом списке
        std::cout << "deleteLess на пустом списке:" << std::endl;
        list.deleteLess(10);
        
        // Один элемент
        list.insert(42);
        std::cout << "\nСписок с одним элементом: ";
        list.print();
        
        list.removeMax();
        std::cout << "После removeMax: ";
        list.print();
        
        // Все элементы меньше порога
        list.insert(5);
        list.insert(10);
        list.insert(15);
        std::cout << "\nНовый список: ";
        list.print();
        
        list.deleteLess(20);
        std::cout << "После deleteLess(20): ";
        list.print();
        
    } catch (const std::exception& e) {
        std::cerr << "✗ Ошибка: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "==================================" << std::endl;
    std::cout << "  ТЕСТИРОВАНИЕ SINGLYLINKEDARRAY " << std::endl;
    std::cout << "==================================" << std::endl;
    
    test1();
    test2();
    test3();
    test4();
    
    std::cout << "\n==================================" << std::endl;
    std::cout << "        ТЕСТИРОВАНИЕ ЗАВЕРШЕНО    " << std::endl;
    std::cout << "==================================" << std::endl;
    
    return 0;
}