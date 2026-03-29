#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>

template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T key_;
        Node* left_;
        Node* right_;
        Node* p_;

        Node(T key, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr)
            : key_(key), left_(left), right_(right), p_(p) {}
    } ;

    Node* root_;

    void clear(Node* node);

    Node* findNode(const T& key) const;
    void output(std::ostream& out, Node* root) const;
    int getNumberOfNodes(const Node* node) const;
    int getHeight(const Node* node) const;
    void inorderWalk(Node* node) const;
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree<T>& scr) = delete;
    BinarySearchTree<T>& operator=(const BinarySearchTree<T>& scr) = delete;
    BinarySearchTree(BinarySearchTree<T>&& scr) noexcept;
    BinarySearchTree<T>& operator=(BinarySearchTree<T>&& scr) noexcept;
    ~BinarySearchTree();

    bool searchIterative(const T& key) const;
    bool insert(const T& key);
    bool remove(const T& key);
    void output(std::ostream& out) const;
    int getNumberOfNodes() const;
    int getHeight() const;
    void inorderWalkIterative () const;
    void inorderWalk() const;
    void walkByLevels() const;
} ;

#include "BinarySearchTree.tpp"

#endif //BINARY_SEARCH_TREE_H