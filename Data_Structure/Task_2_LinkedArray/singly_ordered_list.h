#ifndef SINGLY_ORDERED_LIST_H
#define SINGLY_ORDERED_LIST_H

#include <iostream>

template<typename T>
class SinglyOrderedList {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
        Node(T&& value) : data(std::move(value)), next(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    size_t size_;

public:
    SinglyOrderedList();
    explicit SinglyOrderedList(const T& value);
    SinglyOrderedList(const SinglyOrderedList& other);
    SinglyOrderedList(SinglyOrderedList&& other) noexcept;
    ~SinglyOrderedList();

    SinglyOrderedList& operator=(const SinglyOrderedList& other);
    SinglyOrderedList& operator=(SinglyOrderedList&& other) noexcept;

    T& head();
    const T& head() const;
    T& tail();
    const T& tail() const;
    bool search(const T& key) const;

    void insert(const T& value);
    void insert(T&& value);

    void removeHead();
    void clear();

    size_t size() const;
    bool isEmpty() const;
    void print() const;

    bool removeKey(const T& key);
    bool operator==(const SinglyOrderedList& other) const;

    template<typename U>
    friend SinglyOrderedList<U> getIntersection(const SinglyOrderedList<U>& list1, const SinglyOrderedList<U>& list2);
    void remove(const SinglyOrderedList& other);
} ;


#include "singly_ordered_list.tpp"

#endif // SINGLY_ORDERED_LIST_H