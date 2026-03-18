#include "QueueList.h"

template<typename T>
QueueList<T>::QueueList() : head(nullptr), tail(nullptr), count(0) {}

template<typename T>
QueueList<T>::~QueueList() {
    while (!isEmpty()) {
        deQueue();
    }
}


template<typename T>
bool QueueList<T>::isEmpty() const {
    return count == 0;
}

template<typename T>
size_t QueueList<T>::size() const {
    return count;
}


template<typename T>
void QueueList<T>::enQueue(const T& el) {
    Node* newNode = nullptr;

    try {
        newNode = new Node(el);
    }
    catch (const std::bad_alloc& ba) {
        throw QueueOverflow("ERROR: Can't allocate memory");
    }
    catch (...) {
        throw;
    }

    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    ++count;
}

template<typename T>
T QueueList<T>::deQueue() {
    if (isEmpty()) {
        throw QueueUnderflow("Can't delete from empty queue");
    }

    T oldData = head->data;
    Node* temp = head;
    head = head->next;

    if (head == nullptr) {
        tail = nullptr;
    }

    delete temp;
    --count;

    return oldData;
}