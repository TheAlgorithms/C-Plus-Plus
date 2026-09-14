/**
 * @file test_avl_tree.cpp
 * @brief Standalone tests for the AVL tree's public interface.
 * @details Covers rotations, deletion, ownership, terminal output, and a
 * reproducible sequence of operations compared with std::set.
 */

// Keep assertions active when this executable is built in Release mode.
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <initializer_list>
#include <iostream>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <utility>

#include "avl_tree.hpp"

/** @brief Check membership and size against a list of distinct values. */
static void assert_items(const AvlTree<int>& tree,
                         std::initializer_list<int> items) {
    assert(tree.size() == static_cast<int>(items.size()));
    assert(tree.isEmpty() == (items.size() == 0));
    for (int item : items) {
        assert(tree.hasItem(item));
    }
}

/** @brief Check empty operations, repeated clearing, and subsequent reuse. */
static void test_empty_and_clear() {
    AvlTree<int> tree;
    assert_items(tree, {});
    assert(tree.height() == -1);
    assert(!tree.hasItem(42));
    tree.remove(42);
    tree.clear();
    assert_items(tree, {});
    assert(tree.height() == -1);

    tree = AvlTree<int>{5, 3, 8, 1, 4, 7, 9};
    tree.clear();
    assert_items(tree, {});
    assert(tree.height() == -1);
    assert(!tree.hasItem(5));
    tree.clear();
    tree.insert(42);
    assert_items(tree, {42});
    assert(tree.height() == 0);
}

/** @brief Check initializer lists, ignored duplicates, and all four rotations. */
static void test_insertion() {
    AvlTree<int> tree{5, 3, 8, 1, 4, 7, 9, 5};
    assert_items(tree, {1, 3, 4, 5, 7, 8, 9});
    assert(tree.height() == 2);
    tree.insert(3);
    assert_items(tree, {1, 3, 4, 5, 7, 8, 9});
    assert(!tree.hasItem(6));

    const std::initializer_list<int> rotations[] = {
        {3, 2, 1},  // Left-left: rotate right.
        {1, 2, 3},  // Right-right: rotate left.
        {3, 1, 2},  // Left-right: double rotation.
        {1, 3, 2}   // Right-left: double rotation.
    };
    for (const auto& items : rotations) {
        const AvlTree<int> rotated(items);
        assert_items(rotated, {1, 2, 3});
        assert(rotated.height() == 1);
    }
}

/** @brief Check leaf, single-child, and two-child deletion, including the root. */
static void test_removal() {
    AvlTree<int> tree{2, 1, 3};
    tree.remove(99);
    assert_items(tree, {1, 2, 3});
    tree.remove(1);  // Leaf.
    assert_items(tree, {2, 3});
    tree.remove(2);  // Root with one child.
    assert_items(tree, {3});
    assert(tree.height() == 0);
    tree.remove(3);  // Last node.
    assert_items(tree, {});
    assert(tree.height() == -1);

    tree = AvlTree<int>{4, 2, 6, 1};
    tree.remove(2);  // Non-root node with one child.
    assert_items(tree, {1, 4, 6});
    assert(tree.height() == 1);
    tree.remove(4);  // Successor is the immediate right child.
    assert_items(tree, {1, 6});

    tree = AvlTree<int>{20, 10, 40, 5, 15, 30, 50, 35};
    tree.remove(20);  // Successor 30 has a right child that must be preserved.
    assert_items(tree, {5, 10, 15, 30, 35, 40, 50});
    assert(!tree.hasItem(20));
    assert(tree.height() == 2);
}

/** @brief Each deletion leaves three nodes that must form a balanced tree. */
static void assert_removal_rotation(std::initializer_list<int> items,
                                    int removed) {
    AvlTree<int> tree(items);
    tree.remove(removed);
    assert(tree.size() == 3);
    assert(tree.height() == 1);
    for (int item : items) {
        assert(tree.hasItem(item) == (item != removed));
    }
}

/** @brief Regression checks for rebalancing after deletion in both directions. */
static void test_removal_rotations() {
    assert_removal_rotation({3, 2, 4, 1}, 4);  // Left-left.
    assert_removal_rotation({2, 1, 3, 4}, 1);  // Right-right.
    assert_removal_rotation({3, 1, 4, 2}, 4);  // Left-right.
    assert_removal_rotation({2, 1, 4, 3}, 1);  // Right-left.
}

/** @brief Verify independent copies and reusable moved-from trees. */
static void test_copy_move_and_swap() {
    AvlTree<int> original{2, 1, 3};
    AvlTree<int> copied(original);
    copied.remove(1);
    assert_items(original, {1, 2, 3});
    assert_items(copied, {2, 3});

    AvlTree<int> assigned{99};
    assigned = original;
    original.clear();
    assert_items(assigned, {1, 2, 3});
    assert(assigned.height() == 1);

    AvlTree<int> moved(std::move(copied));
    assert_items(moved, {2, 3});
    assert_items(copied, {});
    assert(copied.height() == -1);
    copied.insert(42);
    assert_items(copied, {42});

    assigned = std::move(moved);
    assert_items(assigned, {2, 3});
    assert(!assigned.hasItem(1));
    assert_items(moved, {});
    assert(moved.height() == -1);
    moved.insert(7);
    swap(assigned, moved);
    assert_items(assigned, {7});
    assert_items(moved, {2, 3});
    assert(assigned.height() == 0);
    assert(moved.height() == 1);
}

/** @brief Verify that the template supports non-integer values. */
static void test_strings() {
    AvlTree<std::string> tree{"pear", "apple", "orange", "pear"};
    assert(tree.size() == 3);
    assert(tree.height() == 1);
    tree.remove("orange");
    assert(!tree.hasItem("orange"));
    assert(tree.hasItem("apple"));
    assert(tree.hasItem("pear"));
    assert(tree.size() == 2);
}

/** @brief Check output through a stream without writing diagrams to the terminal. */
static void test_display() {
    std::ostringstream empty;
    AvlTree<int>{}.display(empty);
    assert(empty.str() == "(empty)\n");

    std::ostringstream singleton;
    AvlTree<int>{500}.display(singleton);
    assert(singleton.str() == "500\n");

    std::ostringstream left;
    AvlTree<int>{2, 1}.display(left);
    assert(left.str() == "  2\n \u2199\n1\n");
    std::ostringstream right;
    AvlTree<int>{1, 2}.display(right);
    assert(right.str() == "1\n \u2198\n  2\n");

    const AvlTree<int> tree{2, 1, 3};
    std::ostringstream output;
    tree.display(output);
    assert(output.str() == "  2\n \u2199 \u2198\n1   3\n");
    assert_items(tree, {1, 2, 3});
    assert(tree.height() == 1);
}

/** @brief Compare mixed operations with std::set using a fixed random seed. */
static void test_against_set() {
    AvlTree<int> tree;
    std::set<int> expected;
    std::mt19937 generator(42);
    std::uniform_int_distribution<int> value(-50, 50);
    std::bernoulli_distribution insert(0.5);

    for (int step = 0; step < 2000; ++step) {
        const int item = value(generator);
        if (insert(generator)) {
            tree.insert(item);
            expected.insert(item);
        } else {
            tree.remove(item);
            expected.erase(item);
        }
        assert(tree.size() == static_cast<int>(expected.size()));
        assert(tree.isEmpty() == expected.empty());
        for (int candidate = -50; candidate <= 50; ++candidate) {
            assert(tree.hasItem(candidate) == (expected.count(candidate) != 0));
        }

        // An AVL of height h needs at least 1 + N(h-1) + N(h-2) nodes.
        int previous = 0;
        int minimum_nodes = 1;
        int maximum_height = -1;
        while (minimum_nodes <= static_cast<int>(expected.size())) {
            const int next = 1 + minimum_nodes + previous;
            previous = minimum_nodes;
            minimum_nodes = next;
            ++maximum_height;
        }
        assert(tree.height() >= (expected.empty() ? -1 : 0));
        assert(tree.height() <= maximum_height);
    }
}

/** @brief Run all AVL tests; an assertion failure terminates with an error. */
int main() {
    test_empty_and_clear();
    test_insertion();
    test_removal();
    test_removal_rotations();
    test_copy_move_and_swap();
    test_strings();
    test_display();
    test_against_set();
    std::cout << "All AVL tree tests passed!\n";
    return 0;
}
