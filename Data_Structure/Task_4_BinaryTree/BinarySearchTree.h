#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

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
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree<T>& source) = delete;
    BinarySearchTree<T>& operator=(const BinarySearchTree<T>& source) = delete;
    BinarySearchTree(BinarySearchTree<T>&& source) noexcept;
    BinarySearchTree<T>& operator=(BinarySearchTree<T>&& source) noexcept;
    ~BinarySearchTree();
} ;

#include "BinaryTreeSearch.tpp"

#endif //BINARY_SEARCH_TREE_H