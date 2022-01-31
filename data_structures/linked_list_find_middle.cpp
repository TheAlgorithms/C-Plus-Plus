/**
 * @file
 * @brief A linked list implementation using nodes to find the middle element
 * @warning This program does not use a sort function to order the linked list, order is based on original data entry, unsigned 32 bit int
 */

#include <iostream> ///for IO operations
#include <cassert>  ///for assert

/**
* @brief Structure for Node
*/
struct Node
{
    Node* next; ///< forward reference
    int val;    ///< variable that holds the value of the node    
};

/**
* @brief Create linked list and add nodes
* @param Node** head passes in a Node* by reference
* @param valueIn is the value of the node to be added
* @returns void
*/
void addNode(struct Node** head, uint32_t valueIn)
{
    
    struct Node* ptr = new Node; /*< Create new Node to store in linked list */
    ptr->val = valueIn;
    ptr->next = nullptr;
    //Points new node's next to the head and makes the new node the head of the linked list
    if(*head != nullptr)
    {
        ptr->next = *head;
        *head = ptr;
    }
    //If head is nullptr, this is the new head of the list
    else
    {
        *head = ptr;
    }
}

/**
* @brief Tortoise and Hare algorithm utilizing a fast and slow pointer
* @returns Middle element of the linked list, if even, returns element one position to the right of the first middle value
* @param struct Node** head passes in a Node* by reference
*/
int midPoint(struct Node** head)
{
    //create two nodes and set them at the head of the linked list
    struct Node* slowptr = *head;
    struct Node* fastptr = *head;
    //ensure loop runs until fastptr reaches the end of the linked list
    //when fastptr reaches the end of the list than slowptr will be at
    //the middle element of the linked list
    while(fastptr && fastptr->next && fastptr->next->next)
    {
        //move by 1 for slowptr
        slowptr = slowptr->next;
        //move by 2 for fastptr
        fastptr = fastptr->next->next;
    }
    //store value of middle node and return the integer value
    uint32_t ans = slowptr->val;
    return ans;
}

/**
* @brief Prints the linked list from the inputted array
* @param int *n array for input
* @param numNodes number of nodes in linked list
* @returns void, prints out linked list
*/
void printArr(uint32_t *n, uint32_t numNodes)
{
    //takes the array from the main function per user specification
    uint32_t sizeOfArr = numNodes;
    //prints until the last element of the array has been reached
    for(int i = 0; i < sizeOfArr; i++)
    {
        if(i != sizeOfArr - 1)
            std::cout<< n[i] << ", ";
        if(i == sizeOfArr - 1)
            std::cout<< n[i] << "" << std::endl;
    }
}

/**
* @brief Tests to make sure that all functions work to create a linked list and find the middle element (odd)
* @returns void
*/
static void test1()
{
    struct Node* front = nullptr;
    addNode(&front, 1);
    addNode(&front, 2);
    addNode(&front, 3);
    addNode(&front, 4);
    addNode(&front, 5);
    uint32_t middle = midPoint(&front);
    assert (middle == 3);   //ensures Tortoise and Hare algorithm finds the middle element
}

/**
* @brief Tests to make sure that all functions work to create a linked list and find the middle element (even)
* @returns void
*/
static void test2()
{
    struct Node* front = nullptr;
    addNode(&front, 1);
    addNode(&front, 2);
    addNode(&front, 3);
    addNode(&front, 4);
    uint32_t middle = midPoint(&front);
    assert (middle == 3);   //ensures Tortoise and Hare algorithm selects second element in pair of middle elements
}

/**
* @brief Main function gathers user input to create a linked list, returning middle element
* @returns 0 on exit
*/
int main()
{
    test1();
    test2();
    struct Node* head = nullptr;
    std::cout<< "How many nodes would you like to insert into the Linked List?" << std::endl;
    int numNodes;
    std::cin>> numNodes;
    uint32_t *n = new uint32_t[numNodes];
    std::cout<< "Enter the node values (press 'Enter' after each value): " << std::endl;
    std::cout<< "*Values must be unsigned integers (32-bit limit)*" << std::endl;

    for(int i = 0; i < numNodes; i++)
    {
        std::cin>> n[i];
        addNode(&head, n[i]);
    }
    
    printArr(n, numNodes);
    //destroys dynamically allocated array
    delete[] n;
    uint32_t midElement = midPoint(&head);
    std::cout<<std::endl;
    std::cout<< "The value of the middle element is: " << midElement << std::endl;
    return 0;
}
