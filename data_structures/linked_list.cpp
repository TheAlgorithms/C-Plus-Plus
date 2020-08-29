/**
 * @file
 * @brief Implementation of singly linked list algorithm.
 *
 * @details
 * The linked list is a form of container used for holding a sequence of
 * values, which can be added, removed and displayed.
 * ### Algorithm
 * Values can be added by iterating to the end of a list(by following
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
 * @brief Data Structures algorithms
 */
namespace data_structures {

/**
 * @namespace linked_list
 * @brief Functions for singly linked list algorithm
 */
namespace linked_list {

/**
 * This function checks if the string passed consists
 * of only digits.
 * @param s To be checked if s contains only integers
 * @returns true if there are only only digits present in the string
 * @returns false if any other character is found
 */
bool isDigit(const std::string &s) {
    // function statements here
    for (char i : s) {
        if (!isdigit(i)) {
            return false;
        }
    }
    return true;
}

/**
 * A link class containing a value and pointer to another link
 */
class link {
 public:
    explicit link(int v = 0, const std::shared_ptr<link> &s = nullptr);

    std::shared_ptr<link> succ;  ///< pointer to the next value on the list
    int val;                     ///< value of the current link
};

/**
 * constructor of the class link
 * @param v is used to initialize class member value
 * @param s is used to initilaize class member succ
 */
link::link(int v, const std::shared_ptr<link> &s) : val(v), succ(s) {}

/**
 * A list class containing a sequence of links
 */
class list {
 public:
    list() {
        first = std::make_shared<link>(); // create a new 'list' instance as a shared pointer
        last = first;
    }

    bool isEmpty();

    void push_back(int new_elem);
    void push_front(int new_elem);
    void erase(int old_elem);
    void display();
    void search(int find_elem);
    void reverse();

 private:
    std::shared_ptr<link> first;  ///< link before the actual first element
    std::shared_ptr<link> last;   ///< last link on the list
};

/**
 * function checks if list is empty
 * @returns true if list is empty
 * @returns false if list is not empty
 */
bool list::isEmpty() {
    if (first == last) {
        return true;
    } else {
        return false;
    }
}

/**
 * function adds new element to the end of the list
 * @param new_elem to be added to the end of the list
 */
void list::push_back(int new_elem) {
    last->succ = std::make_shared<link>(new_elem);
    last = last->succ;
}

/**
 * function adds new element to the beginning of the list
 * @param new_elem to be added to front of the list
 */
void list::push_front(int new_elem) {
    first->succ = std::make_shared<link>(new_elem, first->succ);
}

/**
 * function erases old element from the list
 * @param old_elem to be erased from the list
 */
void list::erase(int old_elem) {
    if (isEmpty()) {
        std::cout << "List is Empty!";
        return;
    }
    std::shared_ptr<link> t = first;
    std::shared_ptr<link> to_be_removed = nullptr;
    while (t != last && t->succ->val != old_elem) {
        t = t->succ;
    }
    if (t == last) {
        std::cout << "Element not found\n";
        return;
    }
    to_be_removed = t->succ;
    t->succ = t->succ->succ;
    to_be_removed.reset();
    if (t->succ == nullptr) {
        last = t;
    }
}

/**
 * function displays all the elements in the list
 * @returns 'void'
 */
void list::display() {
    if (isEmpty()) {
        std::cout << "List is Empty!";
        return;
    }
    std::shared_ptr<link> t = first;
    while (t->succ != nullptr) {
        std::cout << t->succ->val << "\t";
        t = t->succ;
    }
}

/**
 * function searchs for @param find_elem in the list
 * @param find_elem to be searched for in the list
 */
std::shared_ptr<link> list::search(int find_elem) {
    if (isEmpty()) {
        std::cout << "List is Empty!";
        return nullptr;
    }
    std::shared_ptr<link> t = first;
    while (t != last && t->succ->val != find_elem) {
        t = t->succ;
    }
    if (t == last) {
        std::cout << "Element not found\n";
        return nullptr;
    }
    std::cout << "Element was found\n";
    return t->succ;
}
}  // namespace linked_list
}  // namespace data_structures

/**
 * Main function
 * @returns 0 on exit
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
        std::cout << "\n\nEnter you choice : ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "\nEnter the element to be inserted : ";
                std::cin >> s;

                if (data_structures::linked_list::isDigit(s)) {
                    x = std::stoi(s);
                    l.push_back(x);
                } else {
                    std::cout << "Wrong Input!\n";
                }
                break;
            case 2:
                std::cout << "\nEnter the element to be removed : ";
                std::cin >> s;
                if (data_structures::linked_list::isDigit(s)) {
                    x = std::stoi(s);
                    l.erase(x);
                } else {
                    std::cout << "Wrong Input!\n";
                }
                break;
            case 3:
                std::cout << "\nEnter the element to be searched : ";
                std::cin >> s;
                if (data_structures::linked_list::isDigit(s)) {
                    x = std::stoi(s);
                   std::shared_ptr<data_structures::linked_list::link> found = l.search(x);
                } else {
                    std::cout << "Wrong Input!\n";
                }
                break;
            case 4:
                l.display();
                std::cout << "\n";
                break;
            default:
                std::cout << "Invalid Input\n" << std::endl;
                break;
        }
    } while (choice != 0);
    return 0;
}
