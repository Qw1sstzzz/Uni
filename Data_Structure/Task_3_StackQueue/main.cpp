#include "StackVector.h"
#include "QueueList.h"
#include "Errors.h"
#include "getPostfixFromInfix.h"
#include <iostream>

void testStack() {
    std::cout << "\n=== Тест стека ===\n";
    std::cout << "Создаём стек...\n";
    StackVector<int> st;
    
    std::cout << "Добавляем 10...\n";
    st.push(10);
    std::cout << "Добавляем 20...\n";
    st.push(20);
    std::cout << "Добавляем 30...\n";
    st.push(30);
    
    StackVector<int> st2;
    st2.push(1);
    st2.pop();
    st2.pop();
    std::cout << "Стек: " << st2 << std::endl;

    std::cout << "Стек: " << st << std::endl;
    std::cout << "Top: " << st.top() << std::endl;
    std::cout << "Pop: " << st.pop() << std::endl;
    std::cout << "После pop: " << st << std::endl;
    std::cout << "IsEmpty: " << std::boolalpha << st.isEmpty() << std::endl;
}

void testQueue() {
    std::cout << "\n=== Тест очереди ===\n";
    std::cout << "Создаём очередь...\n";
    QueueList<int> q;
    
    std::cout << "Добавляем 1...\n";
    q.enQueue(1);
    std::cout << "Добавляем 2...\n";
    q.enQueue(2);
    std::cout << "Добавляем 3...\n";
    q.enQueue(3);
    
    std::cout << "Очередь: " << q << std::endl;
    std::cout << "Front: " << q.front() << std::endl;
    std::cout << "DeQueue: " << q.deQueue() << std::endl;
    std::cout << "После deQueue: " << q << std::endl;
}

void testPostfix() {
    std::cout << "\n=== Тест постфикса ===\n";
    char postfix[100];
    
    const char* expr1 = "a+b*c";
    std::cout << "-> " << expr1 << "...\n";
    getPostfixFromInfix(expr1, postfix);
    std::cout << expr1 << " -> " << postfix << std::endl;
    
    const char* expr2 = "(a+b)*c";
    std::cout << "-> " << expr2 << "...\n";
    getPostfixFromInfix(expr2, postfix);
    std::cout << expr2 << " -> " << postfix << std::endl;
}

int main() {
    try {
        testStack();
        testQueue();
        testPostfix();
    } catch (const std::exception& e) {
        std::cout << "\nERROR: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "\nnERROR: " << std::endl;
    }
    
    std::cout << "\nПрограмма завершена" << std::endl;
    return 0;
}