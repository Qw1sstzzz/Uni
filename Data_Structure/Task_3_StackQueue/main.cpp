#include "StackVector.h"
#include "QueueList.h"
#include "getPostfixFromInfix.h"
#include <iostream>

void testStack() {
    StackVector<int> st;
    st.push(10);
    st.push(20);
    std::cout << "Top: " << st.top() << std::endl;
    std::cout << "Pop: " << st.pop() << std::endl;
    std::cout << "IsEmpty: " << st.isEmpty() << std::endl;
}

void testQueue() {
    QueueList<int> q;
    q.enQueue(1);
    q.enQueue(2);
    std::cout << "Front: " << q.front() << std::endl;
    std::cout << "DeQueue: " << q.deQueue() << std::endl;
}

void testPostfix() {
    char postfix[100];
    getPostfixFromInfix("a+b*c", postfix);
    std::cout << "a+b*c -> " << postfix << std::endl;
    
    getPostfixFromInfix("(a+b)*c", postfix);
    std::cout << "(a+b)*c -> " << postfix << std::endl;
}

int main() {
    testStack();
    testQueue();
    testPostfix();
    return 0;
}