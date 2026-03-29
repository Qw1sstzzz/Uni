#include "BinarySearchTree.h"

#include <iostream>
#include <stack>
#include <queue>

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
        if (key == current->key_) {
            delete newNode;
            return false;
        }
        else if (key < current->key_) {
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
int BinarySearchTree<T>::getNumberOfNodes(const Node* node) const {
    if (node == nullptr) {
        return 0;
    }
    return 1 + getNumberOfNodes(node->left_) + getNumberOfNodes(node->right_);
}

template <typename T>
int BinarySearchTree<T>::getNumberOfNodes() const {
    return getNumberOfNodes(root_);
}

template <typename T>
int BinarySearchTree<T>::getHeight(const Node* node) const {
    if (node == nullptr) {
        return -1;
    }
    int leftHeight = getHeight(node->left_);
    int rightHeight = getHeight(node->right_);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

template <typename T>
int BinarySearchTree<T>::getHeight() const {
    return getHeight(root_);
}

template <typename T>
void BinarySearchTree<T>::inorderWalk(Node* node) const {
    if (node != nullptr) {
        inorderWalk(node->left_);
        std::cout << node->key_ << " ";
        inorderWalk(node->right_);
    }
}

template <typename T>
void BinarySearchTree<T>::inorderWalk() const {
    inorderWalk(root_);
    std::cout << std::endl;
}


template <typename T>
void BinarySearchTree<T>::inorderWalkIterative() const {
    std::stack<Node*> stack;
    Node* current = root_;

    while ((current != nullptr) || (!stack.empty())) {
        while (current != nullptr) {
            stack.push(current);
            current = current->left_;
        }
        current = stack.top();
        stack.pop();
        std::cout << current->key_ << " ";
        current = current->right_;
    }
    std::cout << std::endl;
} 


template <typename T>
void BinarySearchTree<T>::walkByLevels() const {
    if (root_ == nullptr) {
        return;
    }

    std::queue<Node*> q;
    q.push(root_);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        std::cout << current->key_ << " ";

        if (current->left_) {
            q.push(current->left_);
        }
        if (current->right_) {
            q.push(current->right_);
        }
    }
    std::cout << std::endl;
}

template <typename T>
void BinarySearchTree<T>::output(std::ostream& out, Node* node) const {
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


template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::minimum(Node* node) const {
    while (node->left_ != nullptr) {
        node = node->left_;
    }
    return node;
}

template <typename T>
void BinarySearchTree<T>::transplant(Node* u, Node* v) {
    if (u->p_ == nullptr) {
        root_ = v;
    }
    else if (u == u->p_->left_) {
        u->p_->left_ = v;
    }
    else {
        u->p_->right_ = v;
    }

    if (v != nullptr) {
        v->p_ = u->p_;
    }
}

template <typename T>
bool BinarySearchTree<T>::remove(const T& key) {
    Node* t = findNode(key);
    if (t == nullptr) {
        return false;
    }

    if (t->left_ == nullptr) {
        transplant(t, t->right_);
    }
    else if (t->right_ == nullptr) {
        transplant(t, t->left_);
    }
    else {
        Node* successor = minimum(t->right_);

        if (successor->p_ != t) {
            transplant(successor, successor->right_);
            successor->right_ = t->right_;
            successor->right_->p_ = successor;
        }

        transplant(t, successor);
        successor->left_ = t->left_;
        successor->left_->p_ = successor;
    }
    delete t;
    return true;
}