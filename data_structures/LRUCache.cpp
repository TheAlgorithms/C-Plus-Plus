/**
 * @file
 * @brief Implementation of LRU Cache Data Structure
 * @details
 * This is a multi line
 * description containing links, references,
 * math equations, etc
 * A Least Recently Used (LRU) Cache organizes items in order of use, allowing you 
 * to quickly identify which item hasn't been used for the longest amount of time.
 * Implemented using Static Doubly Circular Linked List
 * @author [Shubh Bansal](https://github.com/proRamLOGO)
 * @see 
 */

#include <iostream>

/**
 * Class documentation
 */
class class_name {
 private:
    int variable;  ///< short info of this variable
    char *message;  ///< short info

 public:
    // other members also documented as below
}

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
    * Accepts 2 values key and value for all new instaces of class node created.
    * @param param1 on-line info about param1
    * @param param2 on-line info about param2
    * @returns void
    */
    node( KEY_TYPE key, VALUE_TYPE val ) {
        this->key = key ;
        this->val = val ;
        this->next = this->prev = nullptr ;
    }
};

/**
 * Class node
 * @tparam KEY_TYPE: Identifies Data type of Key. 
 * @tparam VALUE_TYPE: Identifies Data type of Value. 
 * Class node to build up and implement doubly circular linked lists
 * which will be used as LRU Cache DS.
 */
template<typename KEY_TYPE, typename VALUE_TYPE>
class LRUCache {
public:
    node *root ;
    unordered_map< int, node* > addr ;
    
    LRUCache(int capacity) {
        
        this->root = new node(-1,-1) ;
        node *temp = this->root ;
        for ( int i = 1 ; i < capacity ; ++i ) {
            temp->next = new node(-1,-1) ;
            temp->next->prev = temp ;
            temp = temp->next ;
        }
        temp->next = this->root ;
        this->root->prev = temp ;
        
        // CLL of size capacity initialized.
        
    }
    
    int get(int key) {
        auto found = addr.find(key) ;
        
        if ( found == addr.end() )
            return -1 ;
        
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
    
    void put(int key, int value) {
        
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
 * Function documentation
 * @tparam T this is a one-line info about T
 * @param param1 on-line info about param1
 * @param param2 on-line info about param2
 * @returns `true` if ...
 * @returns `false` if ...
 */
template<class T>
bool func(int param1, T param2) {
    // function statements here
    if (/*something bad*/) {
        return false;
    }

    return true;
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test(); // execute the tests
    // code here
    return 0;
}
