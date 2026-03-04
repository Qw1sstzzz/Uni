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


template<typename T>
void SinglyOrderedList<T>::insert(const T& value) {
    Node* newNode = nullptr;
    try {
        newNode = new Node(value);
    } 
    catch(...) {
        throw std::runtime_error("Unknown error occurred while creating node");
    }

    try {
        if (isEmpty()) {
            head_ = newNode;
            tail_ = newNode;
            size_ = 1;
            return;
        }

        if (value < head_->data) {
            newNode->next = head_;
            head_ = newNode;
            size_++;
            return;
        }

        Node* current = head_;
        while ((current->next != nullptr) && (current->next->data < value)) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;

        if (newNode->next == nullptr) {
            tail_ = newNode;
        }
        size_++;
    }
    catch (...) {
        delete newNode;
        throw std::runtime_error("Unknown error during insertion");
    }
}


template<typename T>
bool SinglyOrderedList<T>::search(const T& key) const {
    Node* current = head_;

    while (current != nullptr) {
        if (current->data == key) {
            return true;
        }

        if (key < current->data) {
            return false;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
void SinglyOrderedList<T>::removeHead() {
    if (isEmpty()) {
        throw std::runtime_error("Cannot remove head from empty list");
    }

    Node* temp = head_;
    head_ = head_->next;

    if (head_ == nullptr) {
        tail_ = nullptr;
    }

    delete temp;
    size--;
}

template<typename T>
bool SinglyOrderedList<T>::removeKey(const T& key) {
    if (isEmpty()) {
        return false;
    }

    if (head_->data == key) {
        removeHead();
        return true;
    }

    Node* current = head_;
    while ((current->next != nullptr) && (current->next->data < key)) {
        current = current->next;
    }

    if ((current->next != nullptr) && (current->next->data == key)) {
        Node* temp = current->next;
        current->next = temp->next;

        if (temp == tail_) {
            tail_ = current;
        }

        delete temp;
        size_--;
        return true;
    }
    return false;
}


template<typename T>
SinglyOrderedList<T>::SinglyOrderedList(const SinglyOrderedList& other) : head_(nullptr), tail_(nullptr), size_(0) {
    if (other.isEmpty()) {
        return;
    }
    try {
        head_ = new Node(other.head_->data);
        tail_ = head_;
        size_ = 1;

        Node* currentOther = other.head_->next;
        Node* currentThis = head_;

        while (currentOther != nullptr) {
            Node* newNode = newNode(currentOther->data);
            currentThis->next = newNode;
            tail_ = newNode;

            currentThis = newNode;
            currentOther = currentOther->next;
            size++;
        }
    }
    catch (...) {
        clear();
        throw;
    }
}