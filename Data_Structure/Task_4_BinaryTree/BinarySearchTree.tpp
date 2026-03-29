#include "BinarySearchTree.h"
#include <algorithm>

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


template <typename T>
bool BinarySearchTree<T>::insert(const T& key) {
    Node* newNode = new Node(key);

    if (root_ == nullptr) {
        root_ = newNode;
        return true;
    }

    Node* current = root_;
    Node* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (key = current->key_) {
            delete newNode;
            return false;
        }
        else if (key < current->key) {
            current = current->left_;
        }
        else {
            current = current->right_;
        }
    }

    if (key < parent->key) {
        parent->left_ = newNode;
    }
    else {
        parent->right_ = newNode;
    }
    return true;
}

template <typename T>
int BinarySearchTree<T>::getNumberOfNodes(const Node* node) const {
    if (node == nullptr) {
        return 0;
    }
    return 1 + getNumberOfNodes(node->left_) + getNumberOfNodes(node->right_);
}

template <typename T>
int BinarySearchTree<T>::getNumberOfNodes() const {
    return 1 + getNumberOfNodes(root_);
}

template <typename T>
int BinarySearchTree<T>::getHeight(const Node* node) const {
    if (node == nullptr) {
        return -1;
    }
    return 1 + std::max(getHeight(node->left_), getHeight(node->right_));
}

template <typename T>
int BinarySearchTree<T>::getHeight() const {
    return getHeight(root_);
}