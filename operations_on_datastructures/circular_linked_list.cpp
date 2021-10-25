/**
 * @file
 * @brief Implementation for the [Union of two sorted
 * Arrays](https://en.wikipedia.org/wiki/Union_(set_theory))
 * algorithm.
 * @details The Union of two arrays is the collection of all the unique elements
 * in the first array, combined with all of the unique elements of a second
 * array. This implementation uses ordered arrays, and an algorithm to correctly
 * order them and return the result as a new array (vector).
 * @author [Alvin](https://github.com/polarvoid)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace operations_on_datastructures
 * @brief Operations on Data Structures
 */
namespace operations_on_datastructures {

/**
 * @namespace circular_linked_list
 * @brief Functions for the Circular Linked List implementation
 */
namespace circular_linked_list {

/**
 * @brief A Node struct that represents a single node in a Binary Tree
 */
struct Node {
    int64_t data;  ///< The value of the Node
    Node* next;    ///< The Node's successor
    /**
     * @brief Creates a new Node with some initial data
     */
    explicit Node(int64_t _data) {
        data = _data;    ///< Set value of Node data
        next = nullptr;  ///< Initialize successor
    }
    /**
     * @brief Creates a new Node with initial data and a successor
     */
    explicit Node(int64_t _data, Node* _next) {
        data = _data;  ///< Set value of Node data
        next = _next;  ///< Initialize successor
    }
};

class CircularLinkedList {
 private:
    Node* root;  ///< Pointer to the root node
    Node* end;   ///< Pointer to the last node

 public:
    CircularLinkedList() {
        root = nullptr;
        end = nullptr;
    }
};

}  // namespace circular_linked_list

}  // namespace operations_on_datastructures

/**
 * @namespace tests
 * @brief Testcases to check Circular Linkedd List.
 */
namespace tests {}  // namespace tests

/**
 * @brief Function to test the correctness of the circular linked list
 * @returns void
 */
static void test() {}

/**
 * @brief main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
