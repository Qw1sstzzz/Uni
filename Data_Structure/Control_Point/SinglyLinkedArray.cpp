#include "singly_linked_array.h"
#include <iostream>

SinglyLinkedArray::SinglyLinkedArray() : head_(nullptr), tail_(nullptr), size_(0) {}

SinglyLinkedArray::SinglyLinkedArray(SinglyLinkedArray&& other) noexcept
    : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

SinglyLinkedArray::~SinglyLinkedArray() {
    clear();
}

SinglyLinkedArray& SinglyLinkedArray::operator=(SinglyLinkedArray&& other) noexcept {
    if (this != &other) {
        clear();
        
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

SinglyLinkedArray::Node* SinglyLinkedArray::search(const int& key) {
    Node* current = head_;
    while (current != nullptr) {
        if (current->key_ == key) {
            return current;
        }
        current = current->next_;
    }
    return nullptr;
}

void SinglyLinkedArray::insert(const int& key) {
    Node* newNode = new Node(key);
    if (isEmpty()) {
        head_ = tail_ = newNode;
    } else {
        tail_->next_ = newNode;
        tail_ = newNode;
    }
    ++size_;
}

void SinglyLinkedArray::insert(int&& key) noexcept {
    Node* newNode = new Node(std::move(key));
    if (isEmpty()) {
        head_ = tail_ = newNode;
    } else {
        tail_->next_ = newNode;
        tail_ = newNode;
    }
    ++size_;
}

void SinglyLinkedArray::clear() {
    Node* current = head_;
    while (current != nullptr) {
        Node* next = current->next_;
        delete current;
        current = next;
    }
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

size_t SinglyLinkedArray::size() const {
    return size_;
}

bool SinglyLinkedArray::isEmpty() const {
    return head_ == nullptr;
}

void SinglyLinkedArray::print() const {
    if (isEmpty()) {
        std::cout << "(пустой список)" << std::endl;
        return;
    }
    
    Node* current = head_;
    while (current != nullptr) {
        std::cout << current->key_;
        if (current->next_ != nullptr) {
            std::cout << " -> ";
        }
        current = current->next_;
    }
    std::cout << std::endl;
}

void SinglyLinkedArray::removeMax() {
    if (isEmpty()) {
        std::cout << "Список пуст, нечего удалять" << std::endl;
        return;
    }

    if (head_ == tail_) {
        delete head_;
        head_ = tail_ = nullptr;
        size_ = 0;
        return;
    }

    Node* current = head_;
    int max_value = head_->key_;
    
    while (current != nullptr) {
        if (current->key_ > max_value) {
            max_value = current->key_;
        }
        current = current->next_;
    }
    
    std::cout << "Максимальное значение: " << max_value << std::endl;

    while (head_ != nullptr && head_->key_ == max_value) {
        Node* temp = head_;
        head_ = head_->next_;
        delete temp;
        --size_;
    }

    if (head_ == nullptr) {
        tail_ = nullptr;
        return;
    }

    Node* prev = head_;
    current = head_->next_;
    
    while (current != nullptr) {
        if (current->key_ == max_value) {
            prev->next_ = current->next_;
            if (current == tail_) {
                tail_ = prev;
            }
            delete current;
            --size_;
            current = prev->next_;
        } else {
            prev = current;
            current = current->next_;
        }
    }
}

void SinglyLinkedArray::deleteLess(int threshold) {
    if (isEmpty()) {
        std::cout << "Список пуст, нечего удалять" << std::endl;
        return;
    }
    
    std::cout << "Порог удаления: " << threshold << std::endl;

    while (head_ != nullptr && head_->key_ < threshold) {
        Node* temp = head_;
        head_ = head_->next_;
        delete temp;
        --size_;
    }
    
    if (head_ == nullptr) {
        tail_ = nullptr;
        return;
    }

    Node* prev = head_;
    Node* current = head_->next_;
    
    while (current != nullptr) {
        if (current->key_ < threshold) {
            prev->next_ = current->next_;
            if (current == tail_) {
                tail_ = prev;
            }
            delete current;
            --size_;
            current = prev->next_;
        } else {
            prev = current;
            current = current->next_;
        }
    }
}