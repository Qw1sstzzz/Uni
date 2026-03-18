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


template <typename T>
T& QueueList<T>::front() {
    if (isEmpty()) {
        throw QueueUnderflow("Queue is empty");
    }
    return head->data;
}

template <typename T>
const T& QueueList<T>::front() const {
    if (isEmpty()) {
        throw QueueUnderflow("Queue is empty");
    }
    return head->data;
}

template <typename T>
T& QueueList<T>::back() {
    if (isEmpty()) {
        throw QueueUnderflow("Queue is empty");
    }
    return tail->data;
}

template <typename T>
const T& QueueList<T>::back() const {
    if (isEmpty()) {
        throw QueueUnderflow("Queue is empty");
    }
    return tail->data;
}