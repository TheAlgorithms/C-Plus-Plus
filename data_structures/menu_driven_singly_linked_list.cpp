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
 * E.g - 42 --> 45 --> 77 --> 5 --> 20 --> 31
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

vector<string> response = {"Node created",
                           "Node inserted",
                           "Node deleted",
                           "Node not found",
                           "Underflow! List is empty",
                           "Invalid position",
                           "Value updated",
                           "List reversed",
                           "List sorted"};

// creating structure of node
typedef struct node {
    int data;
    node *next;
} node;

/*
 * function : count the size of the list.
 * argument : take a head pointer which points to the first node.
 * returns : count of node in the list (size of list).
 */
int size_of_list(node *head) {
    if (head == NULL) {
        return 0;
    } else {
        node *new_node = head;

        int size_count = 0;

        while (new_node != NULL) {
            new_node = new_node->next;
            size_count++;
        }

        return size_count;
    }
}

/*
 * function : create a node and by default insert the value at the beginning.
 * argument : take a value which is to be inserted.
 * returns : the newly created node (new_node) pointer.
 */
node *create_node(int val) {
    // creating new node
    node *new_node = new node;

    // assigning value to new node data part
    new_node->data = val;

    // assigning null to new node pointer part
    new_node->next = NULL;

    // returning new node
    return new_node;
}

/*
 * function : create a node and insert the value at the beginning.
 * arguments : takes head pointer and value which is to be inserted.
 * returns : the updated head pointer which points to the newly created node.
 */
node *insertion_at_beginning(node *head, int val) {
    // checking if head is null or not
    if (head == NULL) {
        return create_node(val);
    }
    // creating new node
    node *new_node = new node;

    // assigning value to new node data part
    new_node->data = val;

    // assigning head to new node pointer part
    new_node->next = head;

    // head pointer points to the new node
    head = new_node;

    // returning head pointer
    return head;
}

/*
 * function : create a node and insert the value at the given position.
 * arguments : takes head pointer, value and the poistion at which the node is
 * inserted. returns : the updated head pointer which points to the beginning
 * (very first node) node.
 */
node *insertion_at_position(node *head, int val, int pos) {
    // checking position equals to 1
    if (pos == 1)
        insertion_at_beginning(head, val);

    // creating new node 1
    node *new_node_1 = new node;

    // assigning head pointer to the new node
    new_node_1 = head;

    // creating new node 2
    node *new_node_2 = new node;

    // assigning value to new node data part
    new_node_2->data = val;

    // assigning null to new node pointer part
    new_node_2->next = NULL;

    // loop through the list until we get the position
    while (--pos > 1)
        // assigning new node 1 pointer to the new node 1 and try to get the
        // position
        new_node_1 = new_node_1->next;

    // assigning new node 1 pointer to new node 2 pointer
    new_node_2->next = new_node_1->next;

    // assigning new node 2 to new node 1 pointer
    new_node_1->next = new_node_2;

    // returning head pointer
    return head;
}

/*
 * function : create a node and insert the value at the end.
 * arguments : takes head pointer and the value which is to be inserted.
 * returns : the updated head pointer which points to the beginning (very first
 * node) node.
 */
node *insertion_at_end(node *head, int val) {
    // checking if head is null or not
    if (head == NULL) {
        return create_node(val);
    }

    // creating new node 1
    node *new_node_1 = new node;

    // assigning head to new node 1
    new_node_1 = head;

    // loop until we reach the last node
    while (new_node_1->next != NULL)
        // assigning new node 1 pointer to new node 1
        new_node_1 = new_node_1->next;

    // creating new node 2
    node *new_node_2 = new node;

    // assigning value to new node 2 data part
    new_node_2->data = val;

    // assigning null to new node pointer part
    new_node_2->next = NULL;

    // asssigning new node 2 to new node 1 pointer part
    new_node_1->next = new_node_2;

    // returning head pointer
    return head;
}

/*
 * function : delete a node from the beginning of the list.
 * arguments : takes head pointer which points the first node.
 * returns : the updated head pointer which points to the next node after
 * deleting the first node.
 */
node *deletion_from_beginning(node *head) {
    // creating new node
    node *new_node = new node;

    // assigning head to new node
    new_node = head;

    // assigning head pointer part to head
    head = head->next;

    // deleting new node
    delete new_node;

    // returning head pointer
    return head;
}

/*
 * function : delete a node from the given position.
 * arguments : takes head pointer and the position of the node.
 * returns : the updated head pointer which points to the first node after
 * deleting.
 */
node *deletion_from_position(node *head, int pos) {
    // checking position is equals to 1
    if (pos == 1)
        return deletion_from_beginning(head);

    // creating new node 1 and 2
    node *new_node_1 = new node;
    node *new_node_2 = new node;

    // assigning head to new node 1
    new_node_1 = head;

    // loop until we get the position
    while (--pos) {
        // assigning new node 1 to new node 2
        new_node_2 = new_node_1;

        // assigning new node 1 pointer part to new node 1
        new_node_1 = new_node_1->next;
    }

    // assigning new node 1 pointer part to new node 2 pointer part
    new_node_2->next = new_node_1->next;

    // deleteing new node 1
    delete new_node_1;

    // returning head pointer
    return head;
}

/*
 * function : delete a node from the end.
 * arguments : takes head pointer which points to the first node.
 * returns : the updated head pointer which points to the first node after
 * deletion.
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

    // assigning head to new node 1
    new_node_1 = head;

    // loop until we reach at last of the list
    while (new_node_1->next->next != NULL)
        // assigning new node 1 pointer part to new node 1
        new_node_1 = new_node_1->next;

    // creating new node 2
    node *new_node_2 = new node;

    // assigning new node 1 pointer part to new node 1
    new_node_2 = new_node_1->next;

    // deleting new node 2
    delete new_node_2;

    // assigning null to new node 1 pointer part
    new_node_1->next = NULL;

    // returning head
    return head;
}

/*
 * function : update a value in the existing list.
 * arguments : takes head pointer, existing value and the updating value.
 * returns : the updated value and if value is not present then null pointer.
 */
int *updation_of_value(node *head, int existing_val, int updated_val) {
    // creating a new node
    node *new_node = new node;

    // assigning head to new node
    new_node = head;

    // loop until we reach the last of the node
    while (new_node != NULL) {
        // checking if new node data is existing value
        if (new_node->data == existing_val) {
            // updating new node existing value to updating value and returning
            new_node->data = updated_val;
            return &(new_node->data);
        }

        // updating new node next part to new node
        new_node = new_node->next;
    }

    // return null pointer if the value is not founded
    return nullptr;
}

/*
 * function : search a value in the existing list.
 * arguments : takes head pointer and value to be search.
 * returns : if value is found then position of the value else 0.
 */
int search_node(node *head, int val) {
    // creating a new node
    node *new_node = new node;

    // assigning head to new node
    new_node = head;

    int pos = 0;

    // loop until we reach the last of the node
    while (new_node != NULL) {
        pos++;

        // checking if new node data part is equal to value
        if (new_node->data == val)
            return pos;

        // assigning new node next part to new node
        new_node = new_node->next;
    }

    return 0;
}

/*
 * function : merges two subdivided linked list and sort them.
 * arguments : takes head pointer and slow pointer.
 * returns : returns first_head pointer which points to the head of the merge
 * list.
 */
node *mergelist(node *head, node *slow) {
    node *first_head = NULL;
    node *first_tail = NULL;

    while (head != NULL && slow != NULL) {
        if (first_head == NULL && first_tail == NULL) {
            if (head->data > slow->data) {
                first_head = slow;
                first_tail = slow;
                slow = slow->next;
            } else {
                first_head = head;
                first_tail = head;
                head = head->next;
            }
        }
        if (head && slow) {
            if (head->data < slow->data) {
                first_tail->next = head;
                first_tail = first_tail->next;
                head = head->next;
            } else {
                first_tail->next = slow;
                first_tail = first_tail->next;
                slow = slow->next;
            }
        }
    }

    if (head != NULL)
        first_tail->next = head;

    if (slow != NULL)
        first_tail->next = slow;

    return first_head;
}

/*
 * function : sort the existing linked list.
 * arguments : takes head pointer which points to the head of the list.
 * returns : two subdivided linked list to the merge_list() function.
 */
node *sort_list(node *head) {
    if (head == NULL || head->next == NULL)
        return head;

    // creating new node
    node *new_node = new node;

    // creating slow pointer assigning head (moves 1 node at a time)
    node *slow = head;

    // creating fast pointer and assigning head (moves 2 node at a time)
    node *fast = head;

    // loop until we reach the last of list
    while (fast != NULL && fast->next != NULL) {
        // assigning slow to new node
        new_node = slow;

        // assigning next part of slow to slow (moving 1 node)
        slow = slow->next;

        // assigning next part of fast to fast (moving 2 node)
        fast = fast->next->next;
    }

    // assigning null to new node next part
    new_node->next = NULL;

    // creating and assigning subdivided list in list 1 and list 2
    node *list_1 = sort_list(head);
    node *list_2 = sort_list(slow);

    // calling the mergelist function
    return mergelist(list_1, list_2);
}

/*
 * function : reverse the existing linked list.
 * arguments : takes head pointer which points to the head of the list.
 * returns : head pointer which points to the first node of the list.
 */
node *reverse_list(node *head) {
    // assigning null to prev part
    node *prev = NULL;

    // assigning null to next part
    node *next = NULL;

    // loop until the head pointer become null
    while (head != NULL) {
        // assigning next pointer of head to next
        next = head->next;

        // assigning prev pointer to next pointer of head
        head->next = prev;

        // assigning head to previous
        prev = head;

        // assigning head to next
        head = next;
    }

    // assigning previous to head
    head = prev;

    // return head pointer
    return head;
}

/*
 * function : traverse existing linked list.
 * arguments : takes head pointer which points to the head of the list.
 * returns : void (nothing).
 */
int traverse_list(node *head) {
    // creating new node and assigning head to that node
    node *new_node = head;

    // loop until we reach the last of the node
    while (new_node != NULL) {
        cout << new_node->data << " ";

        // assigning new node pointer part to new node
        new_node = new_node->next;
    }

    return 0;
}

/*
 * function : provide menu for the program.
 * arguments : not arguments.
 * returns : void (nothing).
 */
void menu() {
    // creating head node
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
             << "13. Traverse list : " << endl
             << "14. Exit program : " << endl
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
                    cout << response[5] << endl;

                    break;
                }

                head = deletion_from_beginning(head);

                cout << response[2] << endl;

                break;
            }
            case 6: {
                if (size == 0) {
                    cout << response[5] << endl;

                    break;
                }

                head = deletion_from_end(head);

                cout << response[2] << endl;

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

                    cout << response[5] << endl;

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

                if (head == NULL) {
                    cout << response[4] << endl;
                } else {
                    cout << response[7] << endl;
                }

                break;
            }
            case 13: {
                if (size == 0) {
                    cout << response[4] << endl;
                    break;
                }

                cout << "List : ";
                traverse_list(head);

                break;
            }
            case 14: {
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