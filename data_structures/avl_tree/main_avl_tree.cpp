#include <iostream>
#include "avl_tree.hpp"

using namespace std;

int main() {
    AvlTree<int> tree = AvlTree<int>{5, 3, 8, 1, 4, 7, 500};
    tree.display();
    tree.clear();
    cout << "" << tree.isEmpty() << endl;
    return 0;
}
