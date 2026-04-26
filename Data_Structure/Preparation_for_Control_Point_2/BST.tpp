#include "BST.h"
#include <iostream>

template <typename T>
BinarySearchTree<T>::BinarySearchTree() {
    root_ = nullptr;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    clear(root_);
    root_ = nullptr;
}

// template <typename T>
// BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& src) noexcept
//     : root_(src.root_) {
//     src.root_ = nullptr;
// }

// template <typename T>
// BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>&& src) noexcept {
//     if (this != &src) {
//         clear(root_);
//         root_ = src.root_;
//         src.root_ = nullptr;
//     }
//     return *this;
// }

template <typename T>
void BinarySearchTree<T>::clear(Node* node) {
    if (node != nullptr) {
        clear(node->left_);
        clear(node->right_);
        delete node;
    }
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
        if (key == current->key_) {
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

    newNode->p_ = parent;
    if (key < parent->key_) {
        parent->left_ = newNode;
    }
    else {
        parent->right_ = newNode;
    }
    return true;
}

template <typename T>
void BinarySearchTree<T>::output(std::ostream& out, const Node* node) const {
    if (node == nullptr) {
        out << "()";
        return;
    }
    out << "(" << node->key_;
    output(out, node->left_);
    output(out, node->right_);
    out << ")";
}

template <typename T>
void BinarySearchTree<T>::output(std::ostream& out) const {
    output(out, root_);
}
