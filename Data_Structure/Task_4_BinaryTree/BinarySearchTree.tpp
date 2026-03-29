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
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& source) noexcept 
    : root_(source.root_) {
    source.root_ = nullptr;
}

template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>&& source) noexcept {
    if (this != &source) {
        clear(root_);
        root_ = source.root_;
        source.root_ = nullptr;
    }
    return *this;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    clear(root_);
    root_ = nullptr;
}