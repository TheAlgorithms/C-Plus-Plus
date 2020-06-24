#include <iostream>

/**
 * Initialize variables
 */
struct node {
    int val;
    node *next;
};

node *start;

/**
 * Insert a node into list
 */
void insert(int x) {
    node *t = start;
    node *n = new node;
    n->val = x;
    n->next = nullptr;
    if (start != nullptr) {
        while (t->next != nullptr) {
            t = t->next;
        }
        t->next = n;
    } else {
        start = n;
    }
}

/**
 * Remove a node from list
 */
void remove(int x) {
    if (start == nullptr) {
        std::cout << "\nLinked List is empty\n";
        return;
    } else if (start->val == x) {
        node *temp = start;
        start = start->next;
        delete temp;
        return;
    }

    node *temp = start, *parent = start;

    while (temp != nullptr && temp->val != x) {
        parent = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        std::cout << std::endl << x << " not found in list\n";
        return;
    }

    parent->next = temp->next;
    delete temp;
}

/**
 * Search a node from list
 */
void search(int x) {
    node *t = start;
    int found = 0;
    while (t != nullptr) {
        if (t->val == x) {
            std::cout << "\nFound";
            found = 1;
            break;
        }
        t = t->next;
    }
    if (found == 0) {
        std::cout << "\nNot Found";
    }
}

/**
 * Show all nodes from list
 */
void show() {
    node *t = start;
    while (t != nullptr) {
        std::cout << t->val << "\t";
        t = t->next;
    }
}

/**
 * Show all nodes from list (reverse)
 */
void reverse() {
    node *first = start;
    if (first != nullptr) {
        node *second = first->next;
        while (second != nullptr) {
            node *tem = second->next;
            second->next = first;
            first = second;
            second = tem;
        }
        start->next = nullptr;
        start = first;
    } else {
        std::cout << "\nEmpty list";
    }
}

/**
 * Main function
 */
int main() {
    int choice, x;
    do {
        std::cout << "\n0. Exit";
        std::cout << "\n1. Insert";
        std::cout << "\n2. Delete";
        std::cout << "\n3. Search";
        std::cout << "\n4. Print";
        std::cout << "\n5. Reverse";
        std::cout << "\n0. Exit";
        std::cout << "\n\nEnter you choice : ";
        std::cin >> choice;
        switch (choice) {
        case 1:
            std::cout << "\nEnter the element to be inserted : ";
            std::cin >> x;
            insert(x);
            break;
        case 2:
            std::cout << "\nEnter the element to be removed : ";
            std::cin >> x;
            remove(x);
            break;
        case 3:
            std::cout << "\nEnter the element to be searched : ";
            std::cin >> x;
            search(x);
            break;
        case 4:
            show();
            std::cout << "\n";
            break;
        case 5:
            std::cout << "The reversed list: \n";
            reverse();
            show();
            std::cout << "\n";
            break;

        default:
            if (choice == 0) { return }
            std::cout << "Wrong option; type an option : ";
            std::cin >> choice;

            break;
        }
    } while (choice != 0);

    return 0;
}
