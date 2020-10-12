/*
    A simple class for Cicular Linear Linked List
*/
#include "cll.h"

/* Constructor */
cll::cll() {
    head = nullptr;
    total = 0;
}

cll::~cll() { /* Desstructure, no need to fill */
}

/* Display a list. and total element */
void cll::display() {
    if (head == nullptr) {
        std::cout << "List is empty !" << std::endl;
    } else {
        std::cout << "CLL list: ";
        node *current = head;
        for (int i = 0; i < total; i++) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << head->data << std::endl;
        std::cout << "Total element: " << total << std::endl;
    }
}

/* List insert a new value at head in list */
void cll::insert_front(int new_data) {
    node *newNode;
    newNode = new node;
    newNode->data = new_data;
    newNode->next = nullptr;
    if (head == nullptr) {
        head = newNode;
        head->next = head;
    } else {
        node *current = head;
        while (current->next != head) {
            current = current->next;
        }
        newNode->next = head;
        current->next = newNode;
        head = newNode;
    }
    total++;
}

/* List insert a new value at head in list */
void cll::insert_tail(int new_data) {
    node *newNode;
    newNode = new node;
    newNode->data = new_data;
    newNode->next = nullptr;
    if (head == nullptr) {
        head = newNode;
        head->next = head;
    } else {
        node *current = head;
        while (current->next != head) {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = head;
    }
    total++;
}

/* Get total element in list */
int cll::get_size() { return total; }

/* Return true if the requested item (sent in as an argument)
is in the list, otherwise return false */
bool cll::find_item(int item_to_find) {
    if (head == nullptr) {
        std::cout << "List is empty !" << std::endl;
        return false;
    } else {
        node *current = head;
        while (current->next != head) {
            if (current->data == item_to_find) {
                return true;
}
            current = current->next;
        }
        return false;
    }
}

/* Overloading method*/
int cll::operator*() { return head->data; }

/* Overload the pre-increment operator.
   The iterator is advanced to the next node. */
void cll::operator++() {
    if (head == nullptr) {
        std::cout << "List is empty !" << std::endl;
    } else {
        node *current = head;
        while (current->next != head) {
            current = current->next;
        }
        current->next = head->next;
        head = head->next;
    }
    total--;
}
