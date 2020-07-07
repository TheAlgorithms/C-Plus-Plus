/**
 * A skip list is a data structure that is used for storing a sorted list of items with a
 *  help of hierarchy of linked lists that connect increasingly sparse subsequences of the items
 * 
 *  References used: GeeksForGeeks skip list code, https://iq.opengenus.org/skip-list/  Code and PseudoCode.
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <ctime>   

// using namespace std; 
using std::vector;
using std::endl;

#define MAX_LEVEL 2   ///< maximum level of skip list
#define PROBABILITY 0.5      ///< current probability for "coin toss"
  

/**
 *  Node structure [Key][Node*, Node*...]
*/
struct Node { 
    int key;
    //pointer of value 
    void* value;
    //Forward Array
    vector<Node*> forward;
    Node(int key, int level, void* value); 
};

/**
 * Creates node with provided key, level and value
*/
Node::Node(int key, int level, void* value) { 
    this->key = key; 
  
    //Initialization of forward vector
    for (int i = 0; i < (level+1); i++){
        forward.push_back(nullptr);
    }
} 
  
/**
 * SkipList class
*/
class SkipList { 
    int level; 
    Node *header; 
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
 * Skeep List constructor
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
 * Returns random level for skip list;
*/
int SkipList::randomLevel() { 
    int lvl = 0; 
    while(static_cast<float>(std::rand())/RAND_MAX < PROBABILITY && lvl < MAX_LEVEL) lvl++;  
    return lvl; 
} 
  
  
  
/**
 * Inserts elements with given key and value;
 * It's level is computed by randomLevel() function.
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

            //Update current level
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
 * Delete document by key
*/
void SkipList::deleteElement(int key) 
{ 
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
       /*Remove empty levels*/
        while(level>0 &&  header->forward[level] == 0) level--; 
        std::cout << "Deleted" << endl;
    } else {
        std::cout << "Doesn't exist" << endl;
    }
} 
  

/**
 * Searching element in skip list structure
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
 * Display skip list level wise 
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
 * Creates and inserts random 2^[number of levels] elements into the skip lists and than displays it
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
