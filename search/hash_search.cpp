/**
 * \file
 * \brief Hash Search Algorithm - Best Time Complexity Ω(1)
 *
 * \copyright 2020 Arctic2333
 *
 * In this algorithm, we use the method of division and reservation remainder to
 * construct the hash function, and use the method of chain address to solve the
 * conflict, that is, we link a chain list after the data, and store all the
 * records whose keywords are synonyms in the same linear chain list.
 *
 */

#include <cstdlib>
#include <iostream>

#define MAX     6  ///< Determines how much data
#define HASHMAX 5  ///< Determines the length of the hash table

/**
 * Mode of hash detection :
 * Division method
 * \param [in] key to hash
 * \returns hash value for `key`
 */

int h(int key) { return key % HASHMAX; }

class hashnode {
 public:
    int key;         // key value for node
    hashnode* next;  // pointer to next link in chain

    // Constructor
    hashnode() {
        key = 0;
        next = NULL;
    }
    hashnode(int key) {
        this->key = key;
        this->next = NULL;
    }
};

class hashtable {
 public:
    hashnode hashtab[HASHMAX];  // array of hashnode object pointer

    hashtable() {
        for (int i = 0; i < HASHMAX; i++) {
            hashtab[i].next = nullptr;
        }
    }

    ~hashtable() {
        for (int i = 0; i < HASHMAX; i++) {
            hashnode* current = hashtab[i].next;
            while (current != nullptr) {
                hashnode* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    void create_hashtable(int key) {
        int index = h(key);
        hashnode* new_hashnode = new hashnode(key);
        new_hashnode->next = hashtab[index].next;
        hashtab[index].next = new_hashnode;
    }

    int hash_search(int key, int* counter) {
        hashnode* pointer;
        int index = h(key);
        pointer = hashtab[index].next;

        std::cout << "data[" << index << "]: ";

        while (pointer != nullptr) {
            (*counter)++;
            std::cout << "data[" << pointer->key << "]: ";
            if (pointer->key == key)
                return 1;
            else
                pointer = pointer->next;
        }

        return 0;
    }
};

int main() {
    hashtable htable;
    int key, index, counter = 0;  // Key is the value to be found
    index = 0;

    int data[MAX] = {1, 10, 15, 5, 8, 7};  //!< test data

    // Construct hash table
    while (index < MAX) {
        htable.create_hashtable(data[index]);
        index++;
    }
    // output hashtable
    for (int i = 0; i < HASHMAX; i++) {
        std::cout << "hashtab [" << i << "]\n";

        hashnode* temp = htable.hashtab[i].next;

        while (temp != nullptr) {
            std::cout << "[" << temp->key << "] ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    while (key != -1) {
        // Get key from user input or use a test key
        std::cout << "Enter key to search (-1 to exit): ";
        std::cin >> key;

        if (key == -1)
            break;

        if (htable.hash_search(key, &counter)) {
            std::cout << "Search time = " << counter << std::endl;
            counter = 0;
        } else {
            std::cout << "Not found!\n";
        }
        /* The test sample is returned as:
         * data[0]:data[5]:data[15]:data[10]:search time = 3 The search is
         * successful. There are 10 in this set of data */
    }

    return 0;
}
