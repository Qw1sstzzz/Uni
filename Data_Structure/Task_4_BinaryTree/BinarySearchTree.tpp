#include "BinarySearchTree.h"

template<typename T>
void BinarySearchTree<T>::clear(Node* node) {
    if (node) {
        clear(node->left_);
        clear(node->right_);
        delete node;
    }
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree() : root_(nullptr) {}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& src) noexcept 
    : root_(src.root_) {
    src.root_ = nullptr;
}

template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>&& src) noexcept {
    if (this != &src) {
        clear(root_);
        root_ = src.root_;
        src.root_ = nullptr;
    }
    return *this;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    clear(root_);
    root_ = nullptr;
}


template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::findNode(const T& key) const {
    Node* current = root_;
    while(current != nullptr) {
        if (key == current->key_) {
            return current;
        }
        else if (key < current->key_) {
            current = current->left_;
        }
        else {
            current = current->right_;
        }
    }
    return nullptr;
}

template <typename T>
bool BinarySearchTree<T>::searchIterative(const T& key) const {
    return findNode(key) != nullptr;
}