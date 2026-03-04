#include "singly_ordered_list.h"
#include <cstddef>

template<typename T>
SinglyOrderedList<T>::SinglyOrderedList() : head_(nullptr), tail_(nullptr), size_(0) {}

template<typename T>
SinglyOrderedList<T>::SinglyOrderedList(const T& value) : head_(nullptr), tail_(nullptr), size_(0) {
    head_ = new Node(value);
    tail_ = head_;
    size_ = 1;
}

template<typename T>
SinglyOrderedList<T>::SinglyOrderedList(SinglyOrderedList&& other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

template<typename T>
SinglyOrderedList<T>::~SinglyOrderedList() noexcept {
    Node* current = head_;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}
