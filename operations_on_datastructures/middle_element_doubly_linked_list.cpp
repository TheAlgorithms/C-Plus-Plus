/**
 * @file
 * @brief Implementation for a doubly-linked list
 * (https://en.wikipedia.org/wiki/Doubly_LinkedList).
 * @details
 * A doubly-linked list is a data structure
 * of sequentially linked nodes each
 * with pointers to previous and next nodes
 * and a data value. This implementation includes
 * an algorithm to find the middle node.
 * @author [Bryan Etzine](https://github.com/bryetz)
 * @see middle_element_doubly_LinkedList.cpp
 */

#include <cassert>   /// for assert
#include <iostream> /// for IO operations

namespace operations_on_datastructures {

/**
* @namespace LinkedList
* @brief Functions for the doubly-linked list implementation
*/
namespace linked_list {

/**
 * @brief A Node struct representing a node in the list
 */
struct Node {
Node* next = nullptr; ///< default pointer to next node
Node* prev = nullptr; ///< default pointer to previous node
int value = 0; ///< default integer value
};

class LinkedList {

/**
 * @brief Doubly linked list implementation.
 */

private:
    Node* tail = nullptr; ///< default last node pointer
    Node* head = nullptr; ///< default first node pointer
    Node* middle = nullptr; ///< default middle node pointer

public:
    /**
     * @brief Creates an empty LinkedList.
     */
    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    /**
     * @brief Gets head of LinkedList.
     */
    Node* getHead() {
        return head;
    }

    /**
     * @brief Gets tail of LinkedList.
     */
    Node* getTail() {
        return tail;
    }

    /**
     * @brief Gets middle of LinkedList.
     */
    Node* getMiddle() {
        return middle;
    }

    /**
     * @brief Sets middle of LinkedList.
     * @param middle Pointer to set middle
     */
    void setMiddle(Node* node) {
        middle = node;
    }

    /**
     * @brief Finds middle node of a linked list.
     * @details An algorithm using a slow and fast pointer, where the fast pointer
     * is twice as fast as the slow pointer. When the fast pointer reaches the end
     * of the doubly linked list, the slow pointer will be at the middle.
     * @returns A pointer to the middle node.
     */
    Node* findMiddle() {
        Node* slow = head; ///< set slow pointer to start
        Node* fast = head; ///< set fast pointer to start
        if (head != nullptr) {
            while (fast != nullptr && fast->next != nullptr) { ///< while fast pointer can still move
                fast = fast->next->next;  ///< fast advances two nodes
                slow = slow->next;  ///< slow advances one node
            }

            std::cout << "Middle element of linked list: " << slow->value
                      << std::endl;
            return slow;
        } else {
            std::cout << "Linked list is empty." << std::endl;
            return nullptr;
        }
    }

    /**
     * @brief Adds a new node to the end of the list.
     * @param value The integer value of the node
     * @returns void
     */
    void addNode(int value) {
        auto newNode = new Node();
        newNode->value = value;
        if (head == nullptr) {  ///< First node (head) is null. Linked list is empty.
            head = newNode; ///< Set head pointer to first node.
            tail = newNode; /// Set tail pointer to first node.
        } else {                   ///< head is not null. Linked list contains nodes.
            newNode->prev = tail;  ///< tail is the previous node to newNode
            tail->next = newNode;  ///< newNode is next node after tail
            tail = newNode;        ///< newNode is now the tail
        }
    }
    };

} // namespace linked_list

} // namespace operations_on_datastructures

namespace tests {
    using operations_on_datastructures::linked_list::LinkedList;
    using operations_on_datastructures::linked_list::Node;

    static void test() {
        auto linked = new LinkedList(); ///< Create empty linked list.
        int numElements = 0;
        std::cout << "Input number of elements in list: " << std::endl;
        std::cin >> numElements;
        while (numElements <= 1) {
            std::cout << "Input a positive integer greater than 1: " << std::endl;
            std::cin >> numElements;
        }

        std::cout << "Inserting " << numElements << " nodes." << std::endl;
        for (int i = 1; i <= numElements; i++) {
            linked->addNode(i);
        }

        linked->setMiddle(linked->findMiddle());
        if (numElements % 2 == 0) { ///< Even number of elements, two middle nodes
            assert(linked->getMiddle()->value == (numElements / 2) + 1); ///< must be second middle node
        } else { ///< Odd number of elements, one middle node
            assert(linked->getMiddle()->value == (numElements + 1) / 2);
        }
    }
}
    int main() {
        tests::test(); ///< Run self tests.
        return 0;
    }
