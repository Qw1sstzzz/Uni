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


template <typename T>
QueueList<T>::QueueList(const QueueList& other) : head(nullptr), tail(nullptr), count(0) {
    Node* current = other.head;
    while (current != nullptr) {
        enQueue(current->data);
        current = current->next;
    }
}

template <typename T>
QueueList<T>::QueueList(QueueList&& other) noexcept : head(other.head), tail(other.tail), count(other.count) {
    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
}

template <typename T>
void QueueList<T>::swap(QueueList& other) noexcept {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(count, other.count);
}

template <typename T>
QueueList<T>& QueueList<T>::operator=(const QueueList& other) {
    if (this != &other) {
        QueueList<T> temp(other);
        swap(temp);
    }
    return *this;
}

template <typename T>
QueueList<T>& QueueList<T>::operator=(QueueList&& other) noexcept {
    if (this != &other) {
        swap(other);
    }
    return *this;
}