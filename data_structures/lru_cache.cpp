/**
 * @file
 * @brief Implementation of [LRU Cache
 * Data](https://www.geeksforgeeks.org/lru-cache-implementation/) Structure
 * @details
 * A Least Recently Used (LRU) Cache organizes items in order of use, allowing
 * you to quickly identify which item hasn't been used for the longest amount of
 * time. Implemented using Static Doubly Circular Linked List
 * @author [Shubh Bansal](https://github.com/proRamLOGO)
 */

#include <cassert>        /// for assert
#include <iostream>       /// for io operations
#include <unordered_map>  /// for hashmap

/**
 * @namespace data_structures
 * @brief Algorithms with data structures
 */
namespace data_structures {
/**
 * @namespace lru_cache
 * @brief Functions for [Least Recently Used
 * Cache](https://www.geeksforgeeks.org/lru-cache-implementation/)
 * implementation
 */
namespace lru_cache {
/**
 * @brief Class node to build up and implement doubly circular linked lists
 * which will be used as LRU Cache DS.
 */
class node {
 public:
    int key;  ///< Variable to contain value of {key}
    int val;  ///< Variable to contain value of {value} associated with {key}
    node
        *next;  //< Pointer to point on the node appearing next to current node.
    node *prev;  //< Pointer to point on the node appearing previous to current
                 // node.

    /**
     * Constructor Function
     * Accepts 2 parameters key and value for all new instaces of class node
     * created.
     * @param key : Key
     * @param val : Value
     * @returns NOTHING
     */
    node(int key, int val) {
        this->key = key;
        this->val = val;
        this->next = this->prev = nullptr;
    }
};

/**
 * Class LRUCache
 * Main Class LRUCache.
 * Attributes:-
 * - node *root ///< Will contain LRU value
 * - unordered_map< int , node* > ///< To keep track od addresses of all nodes
 * involved in linked list. Methods:-
 * - LRUCache(int): Constructor Function
 * - VALUE_TYPE get(int): Function to query on the LRU
 * - void put(int,int): Function to add/update a key in LRU.
 */
class LRUCache {
 public:
    node *root;
    std::unordered_map<int, node *> addr;

    /**
     * Constructor Function
     * Accepts one parameter, the physical size for LRU.
     * Creates a doubly circular linked list containg {capacity} number of
     * nodes.
     * @param capacity the physical size for LRU as needed for particular
     * instance.
     * @returns NOTHING
     */
    explicit LRUCache(int capacity) {
        this->root = new node(-1, -1);
        node *temp = this->root;
        for (int i = 1; i < capacity; ++i) {
            temp->next = new node(-1, -1);
            temp->next->prev = temp;
            temp = temp->next;
        }
        temp->next = this->root;
        this->root->prev = temp;

        // CLL of size capacity initialized.
    }

    /**
     * get Function
     * Accepts one parameter, the key whose value needs to be returned.
     * If key requested is not present return -1.
     * @param key value for this key is to be returned.
     * @returns NOTHING
     */
    int get(int key) {
        auto found = addr.find(key);

        if (found == addr.end()) {
            return -1;
        }

        if (found->second != this->root) {
            // remove and fix
            found->second->prev->next = found->second->next;
            found->second->next->prev = found->second->prev;

            // add and fix before root
            this->root->prev->next = found->second;
            found->second->prev = this->root->prev;
            this->root->prev = found->second;
            found->second->next = this->root;

        } else {
            this->root = this->root->next;
        }

        return found->second->val;
    }

    /**
     * put Function
     * Accepts two parameters key and value. Updates the value of the key if the
     * key exists. Otherwise, adds the key-value pair to the cache. If the
     * number of keys exceeds the capacity from this operation, the function
     * evicts the least recently used key.
     * @param key the key to be added or updated.
     * @param value value for the respective key to be stored.
     * @returns NOTHING
     */
    void put(uint64_t key, const uint64_t &value) {
        if (addr.find(key) == addr.end()) {
            if (this->root->key != -1 && this->root->val != -1) {
                addr.erase(this->root->key);
            }
            this->root->key = key;
            this->root->val = value;
            addr[key] = this->root;
            this->root = this->root->next;
        }
        get(key);
        addr[key]->val = value;
    }
};
}  // namespace lru_cache
}  // namespace data_structures

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    data_structures::lru_cache::LRUCache lru(
        2);  ///< Created a new LRUCache instace of physical size 2.

    ///< Exectuing vaious functions
    lru.put(1, 1);
    lru.put(2, 2);
    std::cout << lru.get(1) << std::endl;
    lru.put(3, 3);
    std::cout << lru.get(2) << std::endl;
    lru.put(4, 4);
    std::cout << lru.get(1) << std::endl;
    std::cout << lru.get(3) << std::endl;
    std::cout << lru.get(4) << std::endl;

    return 0;
}
