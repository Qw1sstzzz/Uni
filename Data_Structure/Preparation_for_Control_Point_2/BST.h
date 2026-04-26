#ifndef BST_H
#define BST_H

#include <iostream>

struct BalanceReport {
    int missingLeft = 0;
    int missingRight = 0;
    int bothChildren = 0;
    int total = 0;
} ;

template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T key_;
        Node* left_;
        Node* right_;
        Node* p_;

        Node(T key, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr) :
            key_(key), left_(left), right_(right), p_(p) {}
    } ;

    Node* root_;

    void clear(Node* node);
    void output(std::ostream& out, const Node* node) const;
    checkBalance(const Node* node, BalanceReport& report) const;
public:
    BinarySearchTree();
    ~BinarySearchTree();

    BinarySearchTree(const BinarySearchTree<T>& other) = delete;
    BinarySearchTree& operator=(const BinarySearchTree<T>& other) = delete;

    // BinarySearchTree(BinarySearchTree<T>&& other);
    // BinarySearchTree& operator=(BinarySearchTree<T>&& other);

    bool insert(const T& key);
    void output(std::ostream& out) const;
    BalanceReport findImbalancedNodes() const;
} ;


#endif //BST_H
