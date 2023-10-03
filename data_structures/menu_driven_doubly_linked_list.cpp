/**
 * @file
 *
 * @brief Implementation of singly linked list algorithm.
 *
 * @details
 * The linked list is a dynamic data structure which stores the values at random
 * locations in the memory. * It contains a node which is divided into two
 * parts, data and pointer. The linked list nodes are connected with each other
 * with the help of pointers.
 *
 * @example
 * E.g - 42 <--> 45 <--> 77 <--> 5 <--> 20 <--> 31
 *
 * ### Algorithm
 * This is a menu driven algorithm and supports plenty of different operations.
 *
 * #### Operations -: Create node
 *                    Insert at beginning
 *                    Insert at position
 *                    Insert at end
 *                    Deleteion from beginning
 *                    Deletion from position
 *                    Deletion from end
 *                    Updation of a value
 *                    Search a value
 *                    Sort list
 *                    Size of list
 *                    Reverse list
 *                    Traverse list forward
 *                    Traverse list backwards
 *                    Exit
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct node {
    int data;
    node *next;
    node *prev;
} node;

// responses for the success and error
vector<string> response = {"Node created",
                           "Node inserted",
                           "Node deleted",
                           "Node not found",
                           "Underflow! List is empty",
                           "Invalid position",
                           "Value updated",
                           "List reversed",
                           "List sorted"};

/**
 * Calculate the size of the linked list.
 * @param head - A pointer to the head of the linked list.
 * @return The number of nodes in the linked list.
 */
int size_of_list(node *head) {
    // Check if the head is null or not
    if (head == NULL) {
        return 0;
    }

    // Create a new node pointer and initialize it with the head
    node *current_node = head;

    int size_count = 0;

    // Count each node until we reach the end of the list
    while (current_node != NULL) {
        current_node = current_node->next;
        size_count++;
    }

    // Return the size of the list
    return size_count;
}

/** Create a new node with the given value.
 * @param val - The integer value to be stored in the new node.
 * @return - A pointer to the newly created node.
 */
node *create_node(int val) {
    // Create a new node.
    node *new_node = new node;

    // Assign the given value to the data part of the new node.
    new_node->data = val;

    // Initialize the next pointer of the new node to NULL.
    new_node->next = NULL;

    // Initialize the prev pointer of the new node to NULL (for doubly linked
    // list).

    new_node->prev = NULL;

    // Return a pointer to the newly created node.
    return new_node;
}

/** Insert a new node with the given value at the beginning.
 * @param head, val - Head pointer and The integer value to be stored in the new
 * node.
 * @return - A pointer to the newly created node.
 */
node *insertion_at_beginning(node *head, int val) {
    // Create a new node
    node *new_node = new node;
    new_node->data = val;
    new_node->next = head;
    new_node->prev = NULL;

    // Check if the 'head' is not equal to NULL
    if (head != NULL) {
        // Update the 'prev' pointer of the current 'head' to point to the new
        // node
        head->prev = new_node;
    }

    // Update the 'head' pointer to point to the new node, making it the new
    // head
    head = new_node;

    // Return the updated 'head' pointer
    return head;
}

/** Insert a new node with the given value at the end.
 * @param head, val - Head pointer and The integer value to be stored in the new
 * node.
 * @return - A pointer to the newly created node.
 */
node *insertion_at_end(node *head, int val) {
    // Check if the 'head' is NULL, indicating an empty list
    if (head == NULL) {
        // Create and return a new node as the only node in the list
        return create_node(val);
    }

    // Create a new node ('new_node') for the data 'val'
    node *new_node = new node;

    // Assign the 'val' to the data part of 'new_node'
    new_node->data = val;

    // Initialize 'next' pointer of 'new_node' to NULL
    new_node->next = NULL;

    // Create a new node ('current_node') and initialize it to 'head'
    node *current_node = head;

    // Traverse the list until 'current_node' reaches the last node (where
    // 'next' is NULL)
    while (current_node->next != NULL) current_node = current_node->next;

    // Assign 'new_node' to the 'next' pointer of the last node
    current_node->next = new_node;

    // Assign 'current_node' to the 'prev' pointer of 'new_node'
    new_node->prev = current_node;

    // Return the updated 'head'
    return head;
}

/** Insert a new node with the given value at the given position.
 * @param head, val, pos - Head pointer and The integer value and The position
 * value.
 * @return - A pointer to the newly created node.
 */
node *insertion_at_position(node *head, int val, int pos) {
    // Check if the desired position is the beginning (position 1)
    if (pos == 1) {
        // Inserting at the beginning by calling the 'insertion_at_beginning'
        // function
        insertion_at_beginning(head, val);
    }

    // Create a new node
    node *new_node = new node;

    // Assign the 'val' to the data part of the new node
    new_node->data = val;

    // Initialize 'prev' and 'next' pointers of the new node
    new_node->prev = NULL;
    new_node->next = NULL;

    // Check if the desired position is the beginning (position 1)
    if (pos == 1) {
        // Inserting at the beginning of the list
        new_node->next = head;
        if (head != NULL) {
            head->prev = new_node;
        }
        head = new_node;
    } else {
        // Initialize a pointer to the previous node
        node *previous_node = head;

        // Traverse the list to find the node before the desired position
        for (int i = 1; i < pos - 1; i++) {
            if (previous_node != NULL) {
                previous_node = previous_node->next;
            }
        }

        // Check if the previous node is not NULL
        if (previous_node != NULL) {
            // Inserting the new node in the middle of the list
            new_node->next = previous_node->next;
            new_node->prev = previous_node;
            previous_node->next = new_node;

            // Update the 'prev' pointer of the node after the new node if it
            // exists
            if (new_node->next != NULL) {
                new_node->next->prev = new_node;
            }
        }
    }

    // Return the updated head of the list
    return head;
}

/** Delete a node from the beginning.
 * @param head - Head pointer which points to the first node.
 * @return - A pointer to the newly created node.
 */
node *deletion_from_beginning(node *head) {
    // Create a new node ('new_node') to temporarily hold the reference to the
    // current head node
    node *new_node = new node;

    // Assign the 'head' to 'new_node' to preserve the reference to the first
    // node
    new_node = head;

    // Update 'head' to point to the second node, effectively removing the first
    // node
    head = head->next;

    // Delete the original first node (pointed to by 'new_node') to free memory
    delete new_node;

    // Return the updated 'head' pointer, which now points to the new beginning
    // of the list
    return head;
}

/** Delete a node from the end.
 * @param head - Head pointer which points to the first node.
 * @return - A pointer to the newly created node.
 */
node *deletion_from_end(node *head) {
    // checking next of head is null or not
    if (head->next == NULL) {
        // deleting head pointer points node (last node)
        delete head;
        return NULL;
    }

    // creating new node 1
    node *new_node_1 = new node;

    // assingning head to new node 1
    new_node_1 = head;

    // loop until the pointer reach to the last node
    while (new_node_1->next != NULL) {
        new_node_1 = new_node_1->next;
    }

    // creating new node 2
    node *new_node_2 = new node;

    // assigning new node 1 previous part to new node 2
    new_node_2 = new_node_1->prev;

    // assigning null to new node 2 next part
    new_node_2->next = NULL;

    // deleting new node 1
    delete new_node_1;

    // returning head pointer
    return head;
}

/** Delete a node from the given position.
 * @param head, pos - Head pointer which points to the first node and position
 * of the deleting node.
 * @return - A pointer to the newly created node.
 */
node *deletion_from_position(node *head, int pos) {
    // Check if the desired position is the beginning (position 1)
    if (pos == 1)
        return deletion_from_beginning(head);

    // Create a new node ('new_node_1') to temporarily hold the reference to the
    // node to be deleted
    node *new_node_1 = new node;

    // Assign 'head' to 'new_node_1' to start traversal from the head of the
    // list
    new_node_1 = head;

    // Traverse the list until reaching the desired position 'pos'
    while (pos > 1) {
        new_node_1 = new_node_1->next;
        pos--;
    }

    // Create a new node ('new_node_2') to hold the reference to the previous
    // node
    node *new_node_2 = new node;

    // Assign the 'prev' pointer of 'new_node_1' to 'new_node_2'
    new_node_2 = new_node_1->prev;

    // Update the 'next' pointer of 'new_node_2' to skip 'new_node_1'
    new_node_2->next = new_node_1->next;

    // Update the 'prev' pointer of the node following 'new_node_1' to point
    // back to 'new_node_2'
    new_node_1->next->prev = new_node_2;

    // Delete 'new_node_1' to free memory
    delete new_node_1;

    // Set 'new_node_1' to NULL to avoid potential issues
    new_node_1 = NULL;

    // Return the head pointer, which may or may not have changed after deletion
    return head;
}

/** Update a value from the list.
 * @param head, existing_val, updated_val - Head pointer, existing value and
 * updated val. Existing value *replaces the updated value
 * @return - A pointer to the newly created node.
 */
int *updation_of_value(node *head, int existing_val, int updated_val) {
    node *new_node = new node;

    // Assign 'head' to 'new_node' to start from the beginning of the list
    new_node = head;

    // Loop until we reach the last node (new_node != NULL)
    while (new_node != NULL) {
        // Check if the current node's data matches the 'existing_val'
        if (new_node->data == existing_val) {
            // Update the data of the current node to 'updated_val'
            new_node->data = updated_val;

            // Return a pointer to the updated data
            return &(new_node->data);
        }

        // Move 'new_node' to the next node in the list
        new_node = new_node->next;
    }

    // Return a nullptr if the 'existing_val' is not found in the list
    return nullptr;
}

/** Search a value in the list.
 * @param head, val - Head pointer and the search value
 * @return - A pointer to the newly created node.
 */
int search_node(node *head, int val) {
    // Create a new node ('new_node') to temporarily traverse the linked list
    node *new_node = new node;

    // Assign 'head' to 'new_node' to start from the beginning of the list
    new_node = head;

    // Initialize a position counter
    int pos = 0;

    // Loop until we reach the last node (new_node != NULL)
    while (new_node != NULL) {
        // Increment the position counter
        pos++;

        // Check if the current node's data matches the 'val'
        if (new_node->data == val) {
            // Return the position (1-based index) of the found value
            return pos;
        }

        // Move 'new_node' to the next node in the list
        new_node = new_node->next;
    }

    // Return 0 if the 'val' is not found in the list
    return 0;
}

/** Merge two sub-divided liked list.
 * @param head, slow - Head pointer and Slow pointer
 * @return - A pointer to the newly created node.
 */
node *mergelist(node *head, node *slow) {
    // Initialize two pointers, 'fh' (first head) and 'ft' (first tail) for the
    // merged list
    node *fh = NULL;
    node *ft = NULL;

    // Merge the two sorted lists until one of them becomes empty
    while (head != NULL && slow != NULL) {
        // If both 'fh' and 'ft' are NULL (first comparison), set them to the
        // smaller of the two lists
        if (fh == NULL && ft == NULL) {
            if (head->data > slow->data) {
                fh = slow;
                ft = slow;
                slow = slow->next;
            } else {
                fh = head;
                ft = head;
                head = head->next;
            }
        }
        // If both 'head' and 'slow' are not NULL, compare their data values
        if (head && slow) {
            // Append the smaller node to the merged list and update 'ft'
            if (head->data < slow->data) {
                ft->next = head;
                ft = ft->next;
                head = head->next;
            } else {
                ft->next = slow;
                ft = ft->next;
                slow = slow->next;
            }
        }
    }

    // If there are remaining nodes in 'head', append them to the merged list
    if (head != NULL) {
        ft->next = head;
    }

    // If there are remaining nodes in 'slow', append them to the merged list
    if (slow != NULL) {
        ft->next = slow;
    }

    // Return the merged list head ('fh') as the result
    return fh;
}

/** Sort list
 * @param head - Head pointer which points to the first node
 * @return - A pointer to the newly created node.
 */
node *sort_list(node *head) {
    // Base case: If the list is empty or has only one element, it is already
    // sorted
    if (head == NULL || head->next == NULL)
        return head;

    // Create a new node ('new_node') to be used for splitting the list
    node *new_node = new node;

    // Initialize two pointers, 'slow' and 'fast,' to split the list in halves
    node *slow = head;  // Moves 1 node at a time
    node *fast = head;  // Moves 2 nodes at a time

    // Traverse the list until 'fast' reaches the end
    while (fast != NULL && fast->next != NULL) {
        // Assign 'slow' to 'new_node' to mark the midpoint of the list
        new_node = slow;

        // Move 'slow' one step
        slow = slow->next;

        // Move 'fast' two steps
        fast = fast->next->next;
    }

    // Set the 'next' pointer of 'new_node' to NULL, effectively splitting the
    // list into two halves

    new_node->next = NULL;

    // Recursively sort the two halves of the list
    node *list_1 = sort_list(head);
    node *list_2 = sort_list(slow);

    // Merge the sorted sublists 'list_1' and 'list_2' into a single sorted list
    // using 'mergelist' function
    return mergelist(list_1, list_2);
}

/** Reverse list
 * @param head - Head pointer which points to the first node
 * @return - A pointer to the newly created node.
 */
node *reverse_list(node *head) {
    // Initialize three pointers: 'prev_node,' 'current_node,' and 'next_node'
    node *prev_node = nullptr;  // Pointer to the previous node
    node *current_node = head;  // Pointer to the current node
    node *next_node = nullptr;  // Pointer to the next node

    // Iterate through the list to reverse it
    while (current_node != nullptr) {
        next_node = current_node->next;  // Store the next node temporarily
        current_node->next =
            prev_node;  // Reverse the 'next' pointer of the current node
        current_node->prev =
            next_node;  // Reverse the 'prev' pointer of the current node
        prev_node = current_node;  // Move the 'prev_node' pointer forward
        current_node = next_node;  // Move the 'current_node' pointer forward
    }

    // 'prev_node' will now be the new head of the reversed list
    return prev_node;
}

/** Traverse list forward direction
 * @param head - Head pointer which points to the first node
 * @return - A pointer to the newly created node.
 */
void traverse_forward(node *head) {
    // Create a new node ('new_node') and assign 'head' to it to start from the
    // beginning of the list
    node *new_node = head;

    // Loop until the 'new_node' pointer reaches the end of the list (i.e.,
    // becomes NULL)
    while (new_node != NULL) {
        // Print the data of the current node followed by a space
        cout << new_node->data << " ";

        // Move the 'new_node' pointer to the next node in the list
        new_node = new_node->next;
    }
}

/** Traverse list forward direction
 * @param head - Head pointer which points to the first node
 * @return - A pointer to the newly created node.
 */
void traverse_backward(node *head) {
    // Create a new node ('new_node') and assign 'head' to it to start from the
    // beginning of the list
    node *new_node = head;

    // Loop until 'new_node' reaches the last node in the forward direction
    while (new_node->next != nullptr) {
        new_node = new_node->next;
    }

    // Loop in reverse order, traversing the list backward
    while (new_node != nullptr) {
        // Print the data of the current node followed by a space
        cout << new_node->data << " ";

        // Move 'new_node' to the previous node in the list
        new_node = new_node->prev;
    }
}

/** Menu function to drive the program
 * @param - null
 * @return - void.
 */
void menu() {
    node *head = new node;
    head = NULL;

    while (true) {
        int option;

        cout << endl << "Select an option from menu - " << endl << endl;

        cout << "1. Create a node : " << endl
             << "2. Insert at beginning : " << endl
             << "3. Insert at end : " << endl
             << "4. Insert at position : " << endl
             << "5. Delete from beginning : " << endl
             << "6. Delete from end : " << endl
             << "7. Delete from position : " << endl
             << "8. Update a value : " << endl
             << "9. Search node : " << endl
             << "10. Sort list : " << endl
             << "11. Size of list : " << endl
             << "12. Reverse list : " << endl
             << "13. Traverse forward : " << endl
             << "14. Traverse backward : " << endl
             << "15. Exit program : " << endl
             << endl;
        cin >> option;

        int size = size_of_list(head);

        switch (option) {
            case 1: {
                int num;

                cout << "Enter a value : ";
                cin >> num;

                head = create_node(num);

                cout << response[0] << endl;

                break;
            }
            case 2: {
                int num;

                cout << "Enter a value : ";
                cin >> num;

                head = insertion_at_beginning(head, num);

                cout << response[1] << endl;

                break;
            }
            case 3: {
                int num;

                cout << "Enter a value : ";
                cin >> num;

                head = insertion_at_end(head, num);

                cout << response[1] << endl;

                break;
            }
            case 4: {
                int pos, val;

                cout << "Enter position : ";
                cin >> pos;

                if (pos < 1 || pos > size) {
                    if (pos == (size + 1)) {
                        int val;

                        cout << "Enter a value : ";
                        cin >> val;

                        head = insertion_at_end(head, val);

                        cout << response[1] << endl;

                        break;
                    }

                    cout << response[5] << endl;

                    break;
                }

                cout << "Enter a value : ";
                cin >> val;

                head = insertion_at_position(head, val, pos);

                cout << response[1] << endl;

                break;
            }
            case 5: {
                if (size == 0) {
                    cout << response[4] << endl;

                    break;
                }

                head = deletion_from_beginning(head);

                cout << response[2] << endl;

                break;
            }
            case 6: {
                if (size == 0) {
                    cout << response[4] << endl;

                    break;
                }

                head = deletion_from_end(head);

                cout << response[5] << endl;

                break;
            }
            case 7: {
                int pos;

                cout << "Enter a position : ";
                cin >> pos;

                if (pos < 1 || pos > size) {
                    if (pos == (size + 1)) {
                        head = deletion_from_end(head);

                        cout << response[2] << endl;

                        break;
                    }

                    cout << response[4] << endl;

                    break;
                }

                head = deletion_from_position(head, pos);

                cout << response[2] << endl;

                break;
            }
            case 8: {
                if (size == 0) {
                    cout << response[4] << endl;
                    break;
                }

                int existing_val, updating_val;

                cout << "Enter existing value : ";
                cin >> existing_val;

                cout << "Enter updating value : ";
                cin >> updating_val;

                int *res = updation_of_value(head, existing_val, updating_val);

                if (res != nullptr)
                    cout << response[6] << endl;
                else
                    cout << response[3] << endl;

                break;
            }
            case 9: {
                if (size == 0) {
                    cout << response[4] << endl;
                    break;
                }

                int val, pos;

                cout << "Enter a value : ";
                cin >> val;

                pos = search_node(head, val);

                if (pos == 0)
                    cout << response[3] << endl;
                else
                    cout << "Found value " << val << " at position " << pos
                         << endl;

                break;
            }
            case 10: {
                if (size == 0) {
                    cout << response[4] << endl;
                    break;
                }

                head = sort_list(head);

                cout << response[8] << endl;

                break;
            }
            case 11: {
                if (size >= 1) {
                    cout << "Size of list : " << size << endl;
                } else {
                    cout << "Size of list : " << 0 << endl;
                }

                break;
            }
            case 12: {
                if (size == 0) {
                    cout << response[4] << endl;
                    break;
                }

                head = reverse_list(head);

                cout << response[7] << endl;

                break;
            }
            case 13: {
                if (size == 0) {
                    cout << response[4] << endl;

                    break;
                }

                cout << "List : ";

                traverse_forward(head);

                break;
            }
            case 14: {
                if (size == 0) {
                    cout << response[4] << endl;

                    break;
                }

                cout << "List : ";

                traverse_backward(head);

                break;
            }
            case 15: {
                exit(0);
                break;
            }
            default: {
                cout << "Invalid input" << endl;
            }
        }
    }
}

/*
 * function : initialize this program.
 * returns : 0.
 */
int main() {
    // calling menu function
    menu();

    return 0;
}