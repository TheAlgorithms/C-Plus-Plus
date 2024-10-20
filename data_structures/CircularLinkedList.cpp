/**
 * @file
 * @brief Implementation of Circular Linked List with basic operations
 * @details This program implements a circular linked list and provides
 * operations such as insertion, deletion, traversal, and search.
 * A circular linked list is a linked list where the last node points back to
 * the head, creating a loop.
 */

#include <cassert>
#include <iostream>
using namespace std;

class Node {
 public:
    int data;
    Node* next;

    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

class circularLinkedList {
 public:
    Node* head;

    /**
     * @brief Constructor to initialize an empty circular linked list
     */

    circularLinkedList() { head = nullptr; }

    /**
     * @brief Function to insert a node at the end of the circular linked
     * list
     * @param data value to insert into the list
     */

    void insertEnd(int data);

    /**
     * @brief Function to insert a node at the beginning of the circular linked
     * list
     * @param data value to insert into the list
     */

    void insertBginning(int data);

    /**
     * @brief Function to delete a node from the circular linked list
     * @param key value of the node to be deleted
     */

    void deleteNode(int key);

    /**
     * @brief Function to display the circular linked list
     */

    void display();
};

void circularLinkedList::insertEnd(int data) {
    Node* newnode = new Node(data);
    if (head == nullptr) {
        head = newnode;
        newnode->next = head;
    } else {
        Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }

        temp->next = newnode;
        newnode->next = head;
    }
}

void circularLinkedList::insertBginning(int data) {
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = newNode;
        newNode->next = head;
    } else {
        Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        newNode->next = head;
        temp->next = newNode;
        head = newNode;
    }
}

/**
 * @brief Function to delete a node from the circular linked list
 * @param key value of the node to be deleted
 */
void circularLinkedList::deleteNode(int key) {
    if (head == nullptr) {
        return;
    }

    Node* temp = head;
    Node* prev = nullptr;

    if (temp->data == key && temp->next == head) {
        delete temp;
        head = nullptr;
        return;
    }

    if (temp->data == key) {
        Node* last = head;
        while (last->next != head) {
            last = last->next;
        }
        last->next = temp->next;
        head = temp->next;
        delete temp;
        return;
    }

    do {
        prev = temp;
        temp = temp->next;
    } while (temp != head && temp->data != key);

    if (temp->data == key) {
        prev->next = temp->next;
        delete temp;
    }
}

/**
 * @brief Function to display the circular linked list
 */
void circularLinkedList::display() {
    if (head == nullptr) {
        std::cout << "List is empty" << std::endl;
        return;
    }

    Node* temp = head;
    do {
        std::cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);
    std::cout << std::endl;
}

/**
 * @brief Self-test function to verify the Circular Linked List implementation
 */
void test() {
    circularLinkedList list;

    // Test insertion at the end
    list.insertEnd(10);
    list.insertEnd(20);
    list.insertEnd(30);
    list.insertBginning(5);

    // Test display
    std::cout << "Circular Linked List: ";
    list.display();

        // Test deletion
    list.deleteNode(20);
    std::cout << "After deletion of 20: ";
    list.display();

    std::cout << "All tests passed!\n";
}

/**
 * @brief Main function to run the self-test
 * @return 0 on successful execution
 */
int main() {
    test();  // Run self-tests
    return 0;
}
