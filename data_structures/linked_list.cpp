/**
 * @file
 * @brief Implementation of singly linked list algorithm.
 * @details
 * The linked list is a data structure used for holding a sequence of
 * values, which can be added, removed, and displayed.
 *
 * ### Algorithm
 * Values can be added by iterating to the end of a list (by following
 * the pointers) starting from the first link. Whichever link points to null
 * is considered the last link and is pointed to the new value.
 *
 * Values can be removed by also iterating through the list. When the node
 * containing the value is found, the node pointing to the current node is made
 * to point to the node that the current node is pointing to, and then returning
 * the current node to heap store.
 */

#include <iostream>
#include <memory>
#include <string>

/**
 * @namespace data_structures
 * @brief Contains various Data Structures
 */
namespace data_structures {

/**
 * @namespace linked_list
 * @brief Contains functions for the singly linked list algorithm
 */
namespace linked_list {

/**
 * This function checks if the string passed consists of only digits.
 * @param s The string to check
 * @returns true if there are only digits present in the string
 * @returns false if any other character is found
 */
bool isDigit(const std::string &s) {
    for (char i : s) {
        if (!isdigit(i)) {
            return false;
        }
    }
    return true;
}

/**
 * A class representing a link (node) in a singly linked list
 */
class link {
 private:
    int pvalue;                   ///< Value of the current link
    std::shared_ptr<link> psucc;  ///< Pointer to the next link in the list

 public:
    /**
     * Returns the value stored in the link
     * @returns The integer value stored in the link
     */
    int val() { return pvalue; }

    /**
     * Returns the pointer to the next link in the list
     * @returns The pointer to the next link
     */
    std::shared_ptr<link>& succ() { return psucc; }

    /**
     * Constructs a link with the provided value
     * @param value The integer stored in the link (default is 0)
     */
    explicit link(int value = 0) : pvalue(value), psucc(nullptr) {}
};

/**
 * A class representing a singly linked list of links (nodes)
 */
class list {
 private:
    std::shared_ptr<link> first;  ///< Pointer to the first link
    std::shared_ptr<link> last;   ///< Pointer to the last link

 public:
    /**
     * List constructor initializes an empty list
     */
    list() {
        first = std::make_shared<link>();  // Dummy first link
        last = nullptr;                    // Empty list initially
    }

    bool isEmpty();
    void push_back(int new_elem);
    void push_front(int new_elem);
    void erase(int old_elem);
    void display();
    std::shared_ptr<link> search(int find_elem);
};

/**
 * Checks if the list is empty
 * @returns true if the list is empty, false otherwise
 */
bool list::isEmpty() {
    return (last == nullptr);
}

/**
 * Adds a new element to the end of the list
 * @param new_elem The element to be added
 */
void list::push_back(int new_elem) {
    if (isEmpty()) {
        first->succ() = std::make_shared<link>(new_elem);
        last = first->succ();
    } else {
        last->succ() = std::make_shared<link>(new_elem);
        last = last->succ();
    }
}

/**
 * Adds a new element to the beginning of the list
 * @param new_elem The element to be added
 */
void list::push_front(int new_elem) {
    if (isEmpty()) {
        first->succ() = std::make_shared<link>(new_elem);
        last = first->succ();
    } else {
        std::shared_ptr<link> new_link = std::make_shared<link>(new_elem);
        new_link->succ() = first->succ();
        first->succ() = new_link;
    }
}

/**
 * Removes a specific element from the list
 * @param old_elem The element to be removed
 */
void list::erase(int old_elem) {
    if (isEmpty()) {
        std::cout << "List is Empty!\n";
        return;
    }
    std::shared_ptr<link> t = first;
    while (t != last && t->succ()->val() != old_elem) {
        t = t->succ();
    }
    if (t == last) {
        std::cout << "Element not found\n";
        return;
    }
    t->succ() = t->succ()->succ();
    if (t->succ() == nullptr) {
        last = t;
    }
}

/**
 * Displays all the elements in the list
 */
void list::display() {
    if (isEmpty()) {
        std::cout << "List is Empty!\n";
        return;
    }
    std::shared_ptr<link> t = first;
    while (t->succ() != nullptr) {
        std::cout << t->succ()->val() << "\t";
        t = t->succ();
    }
    std::cout << "\n";
}

/**
 * Searches for a specific element in the list
 * @param find_elem The element to search for
 * @returns Pointer to the link if found, nullptr if not
 */
std::shared_ptr<link> list::search(int find_elem) {
    if (isEmpty()) {
        std::cout << "List is Empty!\n";
        return nullptr;
    }
    std::shared_ptr<link> t = first;
    while (t != last && t->succ()->val() != find_elem) {
        t = t->succ();
    }
    if (t == last) {
        std::cout << "Element not found\n";
        return nullptr;
    }
    std::cout << "Element found\n";
    return t->succ();
}

}  // namespace linked_list
}  // namespace data_structures

/**
 * Main function:
 * Interacts with the user for adding, removing, searching, and displaying elements in the list.
 */
int main() {
    data_structures::linked_list::list l;
    int choice = 0;
    int x = 0;
    std::string s;

    do {
        std::cout << "\n1. Insert";
        std::cout << "\n2. Delete";
        std::cout << "\n3. Search";
        std::cout << "\n4. Print";
        std::cout << "\n0. Exit";
        std::cout << "\n\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 0:
                std::cout << "\nQuitting the program...\n";
                break;
            case 1:
                std::cout << "\nEnter the element to be inserted: ";
                std::cin >> s;
                if (data_structures::linked_list::isDigit(s)) {
                    x = std::stoi(s);
                    l.push_back(x);
                } else {
                    std::cout << "Invalid Input!\n";
                }
                break;
            case 2:
                std::cout << "\nEnter the element to be removed: ";
                std::cin >> s;
                if (data_structures::linked_list::isDigit(s)) {
                    x = std::stoi(s);
                    l.erase(x);
                } else {
                    std::cout << "Invalid Input!\n";
                }
                break;
            case 3:
                std::cout << "\nEnter the element to be searched: ";
                std::cin >> s;
                if (data_structures::linked_list::isDigit(s)) {
                    x = std::stoi(s);
                    l.search(x);
                } else {
                    std::cout << "Invalid Input!\n";
                }
                break;
            case 4:
                l.display();
                break;
            default:
                std::cout << "Invalid Input!\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
/* Key Features:
Adding Values (push_back and push_front): Inserts elements at the end or the beginning of the list.
Removing Values (erase): Deletes a specified element from the list.
Searching (search): Finds and prints the location of an element.
Displaying (display): Prints all the elements in the list.*/
