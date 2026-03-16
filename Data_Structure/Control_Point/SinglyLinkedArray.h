#ifndef SINGLY_LINKED_ARRAY_H
#define SINGLY_LINKED_ARRAY_H

#include <iostream>

class SinglyLinkedArray {
private:
    struct Node {
        int key_;
        Node* next_;
        
        explicit Node(int key) : key_(key), next_(nullptr) {}
        Node(int key, Node* next) : key_(key), next_(next) {}
    };
    
    Node* head_;
    Node* tail_;
    size_t size_;
    
public:
    SinglyLinkedArray();
    
    SinglyLinkedArray(const SinglyLinkedArray&) = delete;
    SinglyLinkedArray(SinglyLinkedArray&& other) noexcept;
    
    SinglyLinkedArray& operator=(const SinglyLinkedArray&) = delete;
    SinglyLinkedArray& operator=(SinglyLinkedArray&& other) noexcept;
    
    ~SinglyLinkedArray();
    
    Node* head() const { return head_; }
    Node* tail() const { return tail_; }
    
    int front() const {
        if (isEmpty()) throw std::runtime_error("List is empty");
        return head_->key_;
    }
    
    int back() const {
        if (isEmpty()) throw std::runtime_error("List is empty");
        return tail_->key_;
    }
    
    Node* search(const int& key);
    void insert(const int& key);
    void insert(int&& key) noexcept;
    
    void clear();
    size_t size() const;
    bool isEmpty() const;
    void print() const;
    
    void removeMax();
    void deleteLess(int threshold);
};

#endif // SINGLY_LINKED_ARRAY_H