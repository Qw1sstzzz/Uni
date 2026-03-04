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


template<typename T>
T& SinglyOrderedList<T>::head() {
    if (isEmpty()) {
        throw std::runtime_error("Cannot get head of empty list");
    }
    return head_->data;
}

template<typename T>
const T& SinglyOrderedList<T>::head() const {
    if (isEmpty()) {
        throw std::runtime_error("Cannot get head of empty list");
    }
    return head_->data;
}

template<typename T>
T& SinglyOrderedList<T>::tail() {
    if (isEmpty()) {
        throw std::runtime_error("Cannot get tail of empty list");
    }
    return tail_->data;
}

template<typename T>
const T& SinglyOrderedList<T>::tail() const {
    if (isEmpty()) {
        throw std::runtime_error("Cannot get tail of empty list");
    }
    return tail_->data;
}

template<typename T>
size_t SinglyOrderedList<T>::size() const {
    return size_;
}

template<typename T>
bool SinglyOrderedList<T>::isEmpty() const {
    return (head_ == nullptr) && (size_ == 0);
}

template<typename T>
void SinglyOrderedList<T>::clear() {
    Node* current = head_;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}