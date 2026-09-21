#include <iostream>

#include "avl_tree.hpp"

int main() {
    AvlTree<int> tree{5, 3, 8, 1, 4, 7, 500};
    tree.display();
    tree.clear();
    std::cout << tree.isEmpty() << '\n';
    return 0;
}
