/**
 * A skip list is a data structure that is used for storing a sorted list of items with a
 *  help of hierarchy of linked lists that connect increasingly sparse subsequences of the items
 * 
 *  References used: GeeksForGeeks skip list code, https://iq.opengenus.org/skip-list/ Pseudo Code.
*/

#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <time.h>   

// using namespace std; 
using std::vector;
using std::endl;

#define MAXLVL 2   ///< maximum level of skip list
#define P 0.5      ///< current probability for "coin toss"
  

/**
 *  Node structure [Key][Node*, Node*...]
*/
struct Node { 
    int key; 
    void* value;
    /*Forward Array*/
    vector<Node*> forward;
    Node(int key, int level, void* value); 
};

  
Node::Node(int key, int level, void* value) { 
    this->key = key; 
  
    /*Initialization of forward vector*/
    for (int i = 0; i < (level+1); i++){
        forward.push_back(NULL);
    }
} 
  
// Class for Skip list 
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


  
SkipList::SkipList() { 
    level = 0; 
    /* Header initialization*/
    header = new Node(-1, MAXLVL, NULL); 
} 


SkipList::~SkipList(){
    for(int i=0; i <= level; i++) { 
        Node *node = header->forward[i]; 
        Node* temp;
        while(node != NULL) { 
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
    while(static_cast<float>(std::rand())/RAND_MAX < P && lvl < MAXLVL) lvl++;  
    return lvl; 
} 
  
  
// Insert given key in skip list 
void SkipList::insertElement(int key, void* value) { 
    std::cout << "Inserting" << key << "...";
    Node *x = header; 
    Node *update[MAXLVL+1]; 
    memset(update, 0, sizeof(Node*)*(MAXLVL+1)); 


    for(int i = level; i >= 0; i--) { 
        while(x->forward[i] != NULL && x->forward[i]->key < key)  x = x->forward[i]; 
        update[i] = x; 
    } 

    x = x->forward[0]; 

    bool doesnt_exist = (x == NULL || x->key != key);
    if (doesnt_exist) { 
        int rlevel = randomLevel(); 
  
        if(rlevel > level) { 
            for(int i=level+1;i<rlevel+1;i++) update[i] = header; 

            /*Update current level*/
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
  
  /**Delete document by key*/
void SkipList::deleteElement(int key) 
{ 
    Node *x = header; 
  
    Node *update[MAXLVL+1]; 
    memset(update, 0, sizeof(Node*)*(MAXLVL+1)); 
  
    for(int i = level; i >= 0; i--)  { 
        while(x->forward[i] != NULL  &&  x->forward[i]->key < key)  x = x->forward[i]; 
        update[i] = x; 
    } 
  
    x = x->forward[0]; 
  
    bool doesnt_exist = (x == NULL || x->key != key);

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
        return NULL;
    }
} 
  
// Display skip list level wise 
void SkipList::displayList() { 
    std::cout << "Displaying list:\n" << endl;
    for(int i=0; i <= level; i++) { 
        Node *node = header->forward[i]; 
        std::cout << "Level " << (i) << ": ";
        while(node != NULL) { 
            std::cout << node->key << " ";
            node = node->forward[i]; 
        } 
        std::cout << endl;
    } 
} 
  
int main() 
{ 
    std::srand(time(nullptr));

    SkipList lst;

    for (int j = 0; j < (1 << (MAXLVL+1)); j++){
         int k = (std::rand()%( 1 << (MAXLVL+2)) + 1);
         lst.insertElement(k, &j); 
    }

    lst.displayList();

} 
