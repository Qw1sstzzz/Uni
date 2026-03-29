#include <iostream>

#include "BinarySearchTree.h"

int main() {
    BinarySearchTree<int> tree1;
    BinarySearchTree<int> tree2;

    std::cout << "===== TEST 1: Insertion =====" << std::endl;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : values) {
        tree1.insert(v);
    }
    
    std::cout << "Nodes count: " << tree1.getNumberOfNodes() << std::endl;
    std::cout << "Tree height: " << tree1.getHeight() << std::endl;
    std::cout << "Structure: ";
    tree1.output(std::cout);
    std::cout << "\n\n";

    std::cout << "===== TEST 2: Tree Walks =====" << std::endl;
    std::cout << "Inorder (Recursive): ";
    tree1.inorderWalk();
    
    std::cout << "Inorder (Iterative): ";
    tree1.inorderWalkIterative();
    
    std::cout << "Level-order (BFS):   ";
    tree1.walkByLevels();
    std::cout << "\n";

    std::cout << "===== TEST 3: Search & Remove =====" << std::endl;
    std::cout << "Search 40: " << (tree1.searchIterative(40) ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 99: " << (tree1.searchIterative(99) ? "Found" : "Not Found") << std::endl;
    
    std::cout << "Removing 30 (node with two children)..." << std::endl;
    tree1.remove(30);
    std::cout << "Inorder after remove: ";
    tree1.inorderWalk();
    std::cout << "\n";

    std::cout << "===== TEST 4: Common Keys =====" << std::endl;
    tree2.insert(100);
    tree2.insert(200);
    std::cout << "Check tree1 and tree2 (no common): " << (tree1.hasCommonKeys(tree2) ? "YES" : "NO") << std::endl;
    
    std::cout << "Inserting 60 into tree2..." << std::endl;
    tree2.insert(60);
    std::cout << "Check tree1 and tree2 (has common): " << (tree1.hasCommonKeys(tree2) ? "YES" : "NO") << std::endl;
    std::cout << "\n";

    std::cout << "===== TEST 5: Move Semantics =====" << std::endl;
    BinarySearchTree<int> tree3 = std::move(tree1);
    std::cout << "Tree3 nodes after move: " << tree3.getNumberOfNodes() << std::endl;
    std::cout << "Tree1 nodes after move: " << tree1.getNumberOfNodes() << " (Expected: 0)" << std::endl;

    std::cout << "\n===== ALL TESTS COMPLETED =====" << std::endl;

    return 0;
}