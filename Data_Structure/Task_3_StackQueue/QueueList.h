#ifndef QUEUE_LIST_H
#define QUEUE_LIST_H

#include <iostream>
#include "Queue.h"
#include "Errors.h"

template<typename T>
class QueueList : public Queue<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    } ;

    Node* head;
    Node* tail;
    size_t count;
public:
    QueueList();
    QueueList(const QueueList& other);
    QueueList(QueueList&& other) noexcept;
    ~QueueList();

    QueueList& operator=(const QueueList& other);
    QueueList& operator=(QueueList&& other) noexcept;

    void enQueue(const T& el) override;
    T deQueue() override;
    bool isEmpty() const override;

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    size_t size() const;

    void swap(QueueList& other) noexcept;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const QueueList<U>& q);
} ;

template<typename T>
std::ostream& operator<<(std::ostream& os, const QueueList<T>& q) {
    os << "[front] ";
    
    typename QueueList<T>::Node* current = q.head;
    while (current != nullptr) {
        os << current->data;
        if (current->next != nullptr) os << " ";
        current = current->next;
    }
    
    os << " [back]";
    return os;
}

#include "QueueList.tpp"

#endif //QUEUE_LIST_H
