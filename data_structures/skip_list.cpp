/**
 * @file skip_list.cpp
 * @brief Data structure for fast searching and insertion in \f$O(\log n)\f$ time
 * @details
 * A skip list is a data structure that is used for storing a sorted list of items with a
 * help of hierarchy of linked lists that connect increasingly sparse subsequences of the items
 * 
 * References used: [GeeksForGeek](https://www.geeksforgeeks.org/skip-list/), [OpenGenus](https://iq.opengenus.org/skip-list) for PseudoCode and Code
 * @author [enqidu](https://github.com/enqidu)
 * .
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <ctime>   

using std::vector;
using std::endl;

#define MAX_LEVEL 2   ///< Maximum level of skip list
#define PROBABILITY 0.5      ///< Current probability for "coin toss"
  

/**
 *  Node structure [Key][Node*, Node*...]
*/
struct Node { 
    int key; ///< key integer
    void* value;  ///< pointer of value 
    vector<Node*> forward;  ///< nodes of the given one in all levels
    // Constructor of the node
    Node(int key, int level, void* value); 
};

/**
 * Creates node with provided key, level and value
 * @param key is number that is used for comparision
 * @param level is the maximum level node's going to added
*/
Node::Node(int key, int level, void* value) { 
    this->key = key; 
  
    //Initialization of forward vector
    for (int i = 0; i < (level+1); i++){
        forward.push_back(nullptr);
    }
} 
  
/**
 * SkipList class implementation with basic methods
*/
class SkipList { 
    int level;  ///< Maximum level of the skiplist
    Node *header; ///< Pointer to the header node
public: 
    SkipList(); 
    int randomLevel(); 
    void insertElement(int, void*); 
    void deleteElement(int); 
    void* searchElement(int); 
    void displayList(); 
    ~SkipList();
};


/**
 * Skeep List constructor. Initializes header, start
 * Node for searching in the list
*/
SkipList::SkipList() { 
    level = 0; 
    // Header initialization
    header = new Node(-1, MAX_LEVEL, nullptr); 
} 

/**
 * Destructor for skiplist class
*/
SkipList::~SkipList(){
    for(int i=0; i <= level; i++) { 
        Node *node = header->forward[i]; 
        Node* temp;
        while(node != nullptr) { 
            temp = node;
            node = node->forward[i];
            delete temp;
        } 
    } 
    delete header;
}

  
/**
 * Returns random level of the skip list.
 * Every higher level is 2 times less likely.
 * @return lvl: random level for skip list;
*/
int SkipList::randomLevel() { 
    int lvl = 0; 
    while(static_cast<float>(std::rand())/RAND_MAX < PROBABILITY && lvl < MAX_LEVEL) lvl++;  
    return lvl; 
} 
  
  
  
/**
 * Inserts elements with given key and value;
 * It's level is computed by randomLevel() function.
 * @param key is number that is used for comparision
 * @param value pointer to a value, that can be any type
*/
void SkipList::insertElement(int key, void* value) { 
    std::cout << "Inserting" << key << "...";
    Node *x = header; 
    Node *update[MAX_LEVEL+1]; 
    memset(update, 0, sizeof(Node*)*(MAX_LEVEL+1)); 


    for(int i = level; i >= 0; i--) { 
        while(x->forward[i] != nullptr && x->forward[i]->key < key)  x = x->forward[i]; 
        update[i] = x; 
    } 

    x = x->forward[0]; 

    bool doesnt_exist = (x == nullptr || x->key != key);
    if (doesnt_exist) { 
        int rlevel = randomLevel(); 
  
        if(rlevel > level) { 
            for(int i=level+1;i<rlevel+1;i++) update[i] = header; 

            // Update current level
            level = rlevel; 
        } 
  
        Node* n = new Node(key, rlevel, value);
        for(int i=0;i<=rlevel;i++) { 
            n->forward[i] = update[i]->forward[i]; 
            update[i]->forward[i] = n; 
        } 
        std::cout << "Inserted" << endl;

    } else {
        std::cout << "Exists" << endl;
    }
} 
  
/**
 * Deletes an element by key and prints if has been removed successfully 
 * @param key is number that is used for comparision.
*/
void SkipList::deleteElement(int key) { 
    Node *x = header; 
  
    Node *update[MAX_LEVEL+1]; 
    memset(update, 0, sizeof(Node*)*(MAX_LEVEL+1)); 
  
    for(int i = level; i >= 0; i--)  { 
        while(x->forward[i] != nullptr  &&  x->forward[i]->key < key)  x = x->forward[i]; 
        update[i] = x; 
    } 
  
    x = x->forward[0]; 
  
    bool doesnt_exist = (x == nullptr || x->key != key);

    if(!doesnt_exist) { 
        for(int i=0;i<=level;i++) {
            if(update[i]->forward[i] != x)  break; 
            update[i]->forward[i] = x->forward[i]; 
        }
       /* Remove empty levels*/
        while(level>0 &&  header->forward[level] == 0) level--; 
        std::cout << "Deleted" << endl;
    } else {
        std::cout << "Doesn't exist" << endl;
    }
} 
  

/**
 * Searching element in skip list structure
 * @param key is number that is used for comparision
 * @return pointer to the value of the node
*/
void* SkipList::searchElement(int key) { 
    Node *x = header; 
    std::cout << "Searching for " + key << endl;

    for(int i = level; i >= 0; i--) { 
        while(x->forward[i] && x->forward[i]->key < key)  x = x->forward[i]; 
    } 
  
    x = x->forward[0]; 
    if(x && x->key == key){
        std::cout << "Found" << endl;
        return x->value;
    } else {
        std::cout << "Not Found" << endl;
        return nullptr;
    }
} 
  
/*
 * Display skip list level
 */
void SkipList::displayList() { 
    std::cout << "Displaying list:\n" << endl;
    for(int i=0; i <= level; i++) { 
        Node *node = header->forward[i]; 
        std::cout << "Level " << (i) << ": ";
        while(node != nullptr) { 
            std::cout << node->key << " ";
            node = node->forward[i]; 
        } 
        std::cout << endl;
    } 
} 


/**
 * Main function:
 * Creates and inserts random 2^[number of levels]
 * elements into the skip lists and than displays it
 */  
int main() 
{ 
    std::srand(std::time(nullptr));

    SkipList lst;

    for (int j = 0; j < (1 << (MAX_LEVEL+1)); j++){
         int k = (std::rand()%( 1 << (MAX_LEVEL+2)) + 1);
         lst.insertElement(k, &j); 
    }

    lst.displayList();

} 
