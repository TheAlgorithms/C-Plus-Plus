/**
 * @file chaining.cpp
 * @author [vasutomar](https://github.com/vasutomar)
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief
 */
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

namespace {  // keep the code local to this file by assigning them to an unnamed
             // namespace
/**
 * @{
 * @brief Define a linked node
 */
struct Node {
    int data{};                         ///< data stored in the node
    std::shared_ptr<struct Node> next;  ///< pointer to the next node
};

/**
 * @brief Chain class with a given modulus
 */
class chain {
 private:
    std::vector<std::shared_ptr<struct Node>> head;  ///< array of nodes
    int _mod;                                        ///< modulus of the class

 public:
    /**
     * @brief Construct a new chain object
     *
     * @param mod modulus of the chain
     */
    chain(int mod) : _mod(mod) {
        while (mod--) head.push_back(nullptr);
    }

    /**
     * @brief create and add a new node with a give value and at a given height
     *
     * @param x value at the new node
     * @param h height of the node
     */
    void add(int x, int h) {
        std::shared_ptr<struct Node> curr;
        std::shared_ptr<struct Node> temp(new struct Node);
        temp->data = x;
        temp->next = nullptr;
        if (!head[h]) {
            head[h] = temp;
            curr = head[h];
        } else {
            curr = head[h];
            while (curr->next) curr = curr->next;
            curr->next = temp;
        }
    }

    /**
     * @brief Display the chain
     */
    void display() {
        std::shared_ptr<struct Node> temp = nullptr;
        int i = 0;
        for (i = 0; i < _mod; i++) {
            if (!head[i]) {
                std::cout << "Key " << i << " is empty" << std::endl;
            } else {
                std::cout << "Key " << i << " has values = ";
                temp = head[i];
                while (temp->next) {
                    std::cout << temp->data << " ";
                    temp = temp->next;
                }
                std::cout << temp->data;
                std::cout << std::endl;
            }
        }
    }

    /**
     * @brief Compute the hash of a value for current chain
     *
     * @param x value to compute modulus of
     * @return modulus of `x`
     */
    int hash(int x) const { return x % _mod; }

    void find(int x, int h) {
        auto temp = head[h];
        if (!head[h]) {
            std::cout << "Element not found";
            return;
        }
        while (temp->data != x && temp->next) temp = temp->next;
        if (temp->next) {
            std::cout << "Element found";
        } else {
            if (temp->data == x) {
                std::cout << "Element found";
            } else {
                std::cout << "Element not found";
            }
        }
    }
};

}  // namespace

/** Main function
 * @returns `0` always
 */
int main() {
    int c = 0, x = 0, mod = 0, h = 0;
    std::cout << "Enter the size of Hash Table. = ";
    std::cin >> mod;

    chain mychain(mod);

    bool loop = true;
    while (loop) {
        std::cout << std::endl;
        std::cout << "PLEASE CHOOSE -" << std::endl;
        std::cout << "1. Add element." << std::endl;
        std::cout << "2. Find element." << std::endl;
        std::cout << "3. Generate Hash." << std::endl;
        std::cout << "4. Display Hash table." << std::endl;
        std::cout << "5. Exit." << std::endl;
        std::cin >> c;
        switch (c) {
            case 1:
                std::cout << "Enter element to add = ";
                std::cin >> x;
                h = mychain.hash(x);
                h = std::abs(h);
                mychain.add(x, h);
                break;
            case 2:
                std::cout << "Enter element to search = ";
                std::cin >> x;
                h = mychain.hash(x);
                mychain.find(x, h);
                break;
            case 3:
                std::cout << "Enter element to generate hash = ";
                std::cin >> x;
                std::cout << "Hash of " << x << " is = " << mychain.hash(x);
                break;
            case 4:
                mychain.display();
                break;
            default:
                loop = false;
                break;
        }
        std::cout << std::endl;
    }
    /*add(1,&head1);
    add(2,&head1);
    add(3,&head2);
    add(5,&head1);
    display(&head1);
    display(&head2);*/
    return 0;
}