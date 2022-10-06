/**
 * @file
 * @brief Rotate a linked list 'n' number of times.
 * @details
 * The linked list is rotated to right side by one step 'n' times.
 **/

#include <cassert> /// for assert
#include <iostream>
#include <memory>

/**
 * @namespace operations_on_datastructures
 * @brief Operations on Data Structures
 */
namespace operations_on_datastructures
{

    /**
     * A link class containing a value and pointer to another link
     */
    class Node
    {
    public:
        int data;                   ///< variable to store data of a node
        std::shared_ptr<Node> next; ///< pointer to the next node
        /**
         * Creates link with provided value and pointer to NULL
         * @param d is the integer stored in the link
         */

        /**
         * Creates link with provided value and pointer to next link
         * @param value is the integer stored in the link
         */
        explicit Node(int d =0) : data(d), next(NULL) {} // Default constructor for Node
    };

    /**
     * A list class containing a sequence of Nodes
     */
    class linked_list
    {
    public:
        std::shared_ptr<Node> head; ///< link before the first element
        std::shared_ptr<Node> tail; ///< last link on the linked list
        /**
         * Linked List constructor. Initializes the head and tail link.
         */
        linked_list()
        {
            // Initialize the first link
            head = std::make_shared<Node>();
            // Initialize the last link with the first link
            tail = head;
        }

        bool isEmpty();
        int countElements();
        void push_back(int d);
        void rotate(int n);
        void display();
    };

    /**
     * function checks if linked list is empty
     * @returns true if linked list is empty
     * @returns false if linked list is not empty
     */
    bool linked_list::isEmpty()
    {
        if (head == nullptr)
            return true;
        else
            return false;
    }

    /**
     * function counts the number of elements in linked list
     * @returns number of elements
     */
    int linked_list::countElements()
    {
        int count = 0;
        std::shared_ptr<Node> temp = head; ///< pointer to iterate through linked list
        while (temp->next != nullptr)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    /**
     * function adds new element to the end of the linked list
     * @param d to be added to the end of the linked list
     */
    void linked_list::push_back(int d)
    {
        if (isEmpty())
        {
            head->next = std::make_shared<Node>(d);
            tail = head->next;
        }
        else
        {
            tail->next = std::make_shared<Node>(d);
            tail = tail->next;
        }
    }

    /**
     * function rotates linked list to the right by given n times
     * @param n times to be rotated
     * @returns 'void'
     */
    void linked_list::rotate(int n)
    {

        int length = countElements(); ///< variable for total number of elements

        /**
          *  if the linked list is rotated as many times as its total number of elements,
             then there is no change in linked list.
        */
        if (n >= length)
        {
            /**
             * eliminate the number of the times the linked list will be rotated back to
               the original linked list
             */
            n = n % length;
        }

        if (n == 0){
            display();
            return; ///< if n beacomes zero; after rotating n times linked list wont be changed
        }

        std::shared_ptr<Node> curr = head; ///< pointer to iterate through linked list
        std::shared_ptr<Node> newtail;     ///< pointer for the new tail to be made

        /// loop for iterationg pointer to the nth element (to be the new head)
        for (int i = 0; i < length-n; ++i)
        {
            curr = curr->next;
        }
        newtail = curr;

        /// loop for iterating pointer to the end of linked list
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = head->next;
        curr = newtail->next;
        newtail->next = NULL;
        head->next = curr;
    }

    /**
     * function displays all the elements in the linked list
     * @returns 'void'
     */
    void linked_list::display()
    {
        if (isEmpty())
        {
            std::cout << "List is Empty!";
            return;
        }
        std::shared_ptr<Node> t = head; ///< pointer to iterate through linked list
        while (t->next != nullptr)
        {
            std::cout << t->next->data << " ";
            t = t->next;
        }
        std::cout << "\n";
    }

}  // namespace operation_on_datastructures

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */

int main(int argc, char *argv[])
{
    operations_on_datastructures::linked_list list; // Initializes the LinkedList
    // Creates a linked lists of total size 10, numbered 1 - 10

    int size; ///< size of linked list
    std::cin>>size;

    int x; ///< temporary variable for taking input data
    for (int i = 0; i < size ; i++)
    {
        std::cin>>x;
        list.push_back(x);
    }

    int rotation; ///< number of times the linked list should be rotated
    std::cin>>rotation;

    // rotate the list
    list.rotate(rotation);

    // display rotated list
    list.display();

    return 0;
}
