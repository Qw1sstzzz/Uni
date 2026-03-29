#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

template <typename T>
class BinarySearchTree {
private:
template <typename U>
    struct Node {
        U key_;
        Node<U>* left_;
        Node<U>* right_;
        Node<U>* p_;

        Node(U key, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr)
            : key_(key), left_(left), right_(right), p_(p) {}
    } ;

    Node<T>* root_;

    void clear(Node<T>* node);

    Node<T>* searchIterative(const T& key) const;
    void output(std::ostream& out, Node<T>* root) const;
    int getNumberOfNodes(const Node<T>* node) const;
    int getHeight(const Node<T>* node) const;
    void inorderWalk(Node<T>* node) const;
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