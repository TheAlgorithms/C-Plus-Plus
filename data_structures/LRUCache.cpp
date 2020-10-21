/**
 * @file
 * @brief Implementation of LRU Cache Data Structure
 * @details
 * A Least Recently Used (LRU) Cache organizes items in order of use, allowing you 
 * to quickly identify which item hasn't been used for the longest amount of time.
 * Implemented using Static Doubly Circular Linked List
 * @author [Shubh Bansal](https://github.com/proRamLOGO)
 * @see 
 */

#include <iostream>  /// for io operations
#include <unordered_map> // For hashmap
#include <cassert>  /// for assert

/**
 * Class node
 * @tparam KEY_TYPE: Identifies Data type of Key. 
 * @tparam VALUE_TYPE: Identifies Data type of Value. 
 * Class node to build up and implement doubly circular linked lists
 * which will be used as LRU Cache DS.
 */
template<typename KEY_TYPE, typename VALUE_TYPE>
class node {
public:
    KEY_TYPE key; ///< Variable to contain value of {key}
    VALUE_TYPE val; ///< Variable to contain value of {value} associated with {key}
    node *next; //< Pointer to point on the node appearing next to current node.
    node *prev ; //< Pointer to point on the node appearing previous to current node.

    /**
    * Constructor Function
    * Accepts 2 parameters key and value for all new instaces of class node created.
    * @param key : Key
    * @param val : Value
    * @returns NOTHING
    */
    node( KEY_TYPE key, VALUE_TYPE val ) {
        this->key = key ;
        this->val = val ;
        this->next = this->prev = nullptr ;
    }
};

/**
 * Class LRUCache
 * @tparam KEY_TYPE: Identifies Data type of Key. 
 * @tparam VALUE_TYPE: Identifies Data type of Value. 
 * Main Class LRUCache.
 * Attributes:-
 * - node *root ///< Will contain LRU value
 * - unordered_map< KEY_TYPE, node* > ///< TO keep trck od addresses of all nodes involved in linked list.
 * Methods:- 
 * - LRUCache(int): Constructor Function
 * - VALUE_TYPE get(KEY_TYPE): Function to query on the LRU
 * - void put(KEY_TYPE, VALUE_TYPE): Function to add/update a key in LRU.
 */
template<typename KEY_TYPE, typename VALUE_TYPE>
class LRUCache {
public:
    node<KEY_TYPE,VALUE_TYPE> *root ;
    unordered_map< KEY_TYPE, node<KEY_TYPE,VALUE_TYPE>* > addr ;

    /**
    * Constructor Function
    * Accepts one parameter, the physical size for LRU.
    * Creates a doubly circular linked list containg {capacity} number of nodes.
    * @param capacity the physical size for LRU as needed for particular instance.
    * @returns NOTHING
    */
    LRUCache(int capacity) {
        
        this->root = new node<KEY_TYPE,VALUE_TYPE>(-1,-1) ;
        node<KEY_TYPE,VALUE_TYPE> *temp = this->root ;
        for ( int i = 1 ; i < capacity ; ++i ) {
            temp->next = new node<KEY_TYPE,VALUE_TYPE>(-1,-1) ;
            temp->next->prev = temp ;
            temp = temp->next ;
        }
        temp->next = this->root ;
        this->root->prev = temp ;
        
        // CLL of size capacity initialized.
        
    }    

    /**
    * get Function
    * Accepts one parameter, the key whose value needs to be returned.
    * If key requested is not present return -1.
    * @param key : value for this key is to be returned.
    * @returns NOTHING
    */
    VALUE_TYPE get(KEY_TYPE key) {
        auto found = addr.find(key) ;
        
        if( found == addr.end() )
            return -1;
        
        if ( found->second != this->root ) {
            //remove and fix 
            found->second->prev->next = found->second->next ;
            found->second->next->prev = found->second->prev ;

            //add and fix before root
            this->root->prev->next = found->second ;
            found->second->prev = this->root->prev ;
            this->root->prev = found->second ;
            found->second->next = this->root ;
        
        } else {
            this->root = this->root->next ;
        }
        
        return found->second->val ;
    }
    
    /**
    * put Function
    * Accepts two parameters key and value. Updates the value of the key if the key exists. 
    * Otherwise, adds the key-value pair to the cache. If the number of keys exceeds the 
    * capacity from this operation, the function evicts the least recently used key.
    * @param key : The key to be added or updated.
    * @param value : Value for the respective key to be stored.
    * @returns NOTHING
    */
    void put(KEY_TYPE key, VALUE_TYPE value) {
        
        if ( addr.find(key) == addr.end() ){
            if ( this->root->key != -1 and this->root->val != -1 ) {
                addr.erase(this->root->key) ;
            }
            this->root->key = key ;
            this->root->val = value ;
            addr[key] = this->root ;
            this->root = this->root->next ;
        }
        get(key) ;
        addr[key]->val = value ;
    }
};

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
   
    LRUCache<KEY_TYPE,VALUE_TYPE> lru(2); ///< Created a new LRUCache instace of physical size 2.
 
    ///< Exectuing vaious functions
    lru.put(1,1);
    lru.put(2,2);
    lru.get(1);
    lru.put(3,3);
    lru.get(2);
    lru.put(4,4);
    lru.get(1);
    lru.get(3);
    lru.get(4);
 
    return 0;
}
