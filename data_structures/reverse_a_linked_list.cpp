/**
 * @file
 * @brief Implementation of reversing a single linked list algorithm.
 * @details
 * The linked list is a data structure used for holding a sequence of
 * values, which can be added, displayed,reversed ,removed.
 * ### Algorithm
 * Values can be added by iterating to the end of a list(by following
 * the pointers) starting from the first link. Whichever link points to null
 * is considered the last link and is pointed to the new value.
 *
 * Linked List can be reversed by using 3 pointers: current, previous, and next_node;
 * we keep iterating until the last node. Meanwhile, before changing to the next
 * of current, we store it in the next_node pointer, now we store the prev
 * pointer in the current of next, this is where the actual reversal happens.
 * And then we move the prev and current pointers one step forward.
 * Then the head node is made to point to the last node (prev pointer) after
 * completion of an iteration.
 */
#include <iostream>

/**
 * A Node class containing a value and pointer to next node;
 */
class Node {
 public:
    int val;     ///< value of the current link
    Node *next;  ///< pointer to the next value on the list
};
/**
 * function adds new element to the end of the list
 * @param n to be added to the end of the list and
 * double pointer to the head node of the list to
 * reflect the changes globally in the whole program
 */
void create(Node **head, int n) {
    Node *new_node = new Node();
    Node *temp = nullptr;
    new_node->val = n;
    new_node->next = nullptr;
    if (*head == nullptr) {
        *head = new_node;
    } else {
        temp = *head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}
/**
 * function displays all the elements in the list
 * @returns void
 * @param node pointer for traversing the list.
 */
void printList(Node *node) {
    while (node != nullptr) {
        std::cout << node->val << "\t";
        node = node->next;
    }
    std::cout << "\n";
}

/**
 * function reverseList for reversing the  list
 * @param double pointer to head node
 */
void reverseList(Node **head) {
    Node *curr = *head;
    Node *prev = nullptr, *next_node = nullptr;
    while (curr != nullptr) {
        next_node = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next_node;
    }
    *head = prev;
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    int n = 0;
    Node *head = nullptr;
    while (true) {
        std::cout << "\n1. Insert";
        std::cout << "\n2. Display";
        std::cout << "\n3. Resverse";
        std::cout << "\n4. Exit";
        std::cout << "\n\nEnter you choice : ";
        std::cin >> n;

        switch (n) {
            case 1: {
                int a = 0;
                std::cout << "\nEnter the element to be inserted : ";
                std::cin >> a;
                create(&head, a);

                break;
            }
            case 2: {
                std::cout << "Printing the Linked List\n";
                std::cout << "\n";
                printList(head);

                break;
            }
            case 3: {
                reverseList(&head);
                break;
            }
            case 4: {
                exit(0);
            }
            default:
                std::cout << "Invalid input\n";
        }
    }
    return 0;
}
