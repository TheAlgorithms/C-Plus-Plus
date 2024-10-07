/**
 * \file
 * \brief Linked list implementation using Arrays
 *
 * The difference between the pointer implementation of linked list and array
 * implementation of linked list:
 * 1. The NULL is represented by -1;
 * 2. Limited size. (in the following case it is 100 nodes at max). But we can
 * reuse the nodes that are to be deleted by again linking it bacj to the list.
 */

#include <iostream>
const int MAX_NODES=100;
const int NULL_VALUE=-1;
struct Node {
    int data;
    int next;
};

Node AvailArray[MAX_NODES];  ///< array that will act as nodes of a linked list.

int head = NULL_VALUE;
int avail = 0;
void initialise_list() {
    for (int i = 0; i < MAX_NODES-1; i++) {
        AvailArray[i].next = i + 1;
    }
    AvailArray[99].next = NULL_VALUE;  // indicating the end of the linked list.
}

/** This will return the index of the first free node present in the avail list
 */
int getnode() {
    if (avail == NULL_VALUE) {
        std::cerr << "Error: No available nodes.\n";
        return NULL_VALUE;
    }
    int NodeIndexToBeReturned = avail;
    avail = AvailArray[avail].next;
    return NodeIndexToBeReturned;
}

/** This function when called will delete the node with
 * the index presented as an argument, and will put
 * back that node into the array.
 */
void freeNode(int nodeToBeDeleted) {
    if(nodeToBeDeleted>=0 && nodeToBeDeleted<MAX_NODES){
        // AvailArray[nodeToBeDeleted].next=avail;
    
    AvailArray[nodeToBeDeleted].next = avail;
    avail = nodeToBeDeleted;
    }
    else{
        std::cerr<<"Error: Invalid node to be deleted.\n";
    }
}

/** The function will insert the given data
 * into the front of the linked list.
 */
void insertAtTheBeginning(int data) {
    int newNode = getnode();
    if(newNode==NULL_VALUE) return;
    AvailArray[newNode].data = data;
    AvailArray[newNode].next = head;
    head = newNode;
}

void insertAtTheEnd(int data) {
    int newNode = getnode();
    // int temp = head;
    if(newNode==NULL_VALUE) return;
   if(head==NULL_VALUE){ 
    // temp is now pointing to the end node.
    AvailArray[newNode].data = data;
    AvailArray[newNode].next = NULL_VALUE;
    // AvailArray[temp].next = newNode;
    head=newNode;
    return;
   }
   int temp = head;
    while (AvailArray[temp].next != NULL_VALUE) {
        temp = AvailArray[temp].next;
    }
    AvailArray[newNode].data = data;
    AvailArray[newNode].next = NULL_VALUE;
    AvailArray[temp].next = newNode;
}

void display() {
    if(head==NULL_VALUE){
        std::cout<<"List is empty.\n";
        return;
    }
    int temp = head;
    while (temp != -1) {
        std::cout << AvailArray[temp].data << "->";
        temp = AvailArray[temp].next;
    }
    std::cout << "NULL" << std::endl;
}
// void automatedChecks() {
//     initialiseList();

//     insertAtTheBeginning(10);
//     insertAtTheBeginning(20);
//     insertAtTheEnd(30);

//     // Assert correct values in the list
//     assert(AvailArray[head].data == 20);  // head should contain 20
//     assert(AvailArray[AvailArray[head].next].data == 10);  // next node should contain 10
//     assert(AvailArray[AvailArray[AvailArray[head].next].next].data == 30);  // last node should contain 30

/** Main function */
int main() {
    initialise_list();
    // automatedChecks();
    int x, y, z;
    for (;;) {
        std::cout << "1. Insert At The Beginning" << std::endl;
        std::cout << "2. Insert At The End" << std::endl;
        std::cout << "3. Display" << std::endl;
        std::cout << "4.Exit" << std::endl;
        std::cout << "Enter Your choice" << std::endl;
        std::cin >> z;
        
        if (std::cin.fail() || z < 1 || z > 4) {
            std::cerr << "Invalid choice, please enter a valid option.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        switch (z) {
        case 1:
            std::cout << "Enter the number you want to enter" << std::endl;
            std::cin >> x;
            insertAtTheBeginning(x);
            break;

        case 2:
            std::cout << "Enter the number you want to enter" << std::endl;
            std::cin >> y;
            insertAtTheEnd(y);
            break;
        case 3:
            std::cout
                << "The linked list contains the following element in order"
                << std::endl;
            display();
            break;
        case 4:
            return 0;
        default:
            std::cout << "The entered choice is not correct" << std::endl;
        }
    }

    return 0;
}
