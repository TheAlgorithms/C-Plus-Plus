// Merge sort is a divide and conquer algorithm, it divides the
// input array into two halves and calls itself for the two halves
// and then calls merge() to merge the two halves
// Worst-Case Time Complexity-> O(n log n)
// Average-Case Time Complexity-> O(n log n)
// Best-Case Time Complexity-> O(n log n)

#include <iostream>
using namespace std;

// node defined
class node {
 public:
    int data;
    node *next;
    node(int data) {
        this->data = data;
        this->next = NULL;
    }
};

// printing the linked list
void print(node *head) {
    node *current = head;
    while (current != NULL) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// creating the linked list with 'n' nodes
node *createlist(int n) {
    node *head = NULL;
    node *t = NULL;
    for (int i = 0; i < n; i++) {
        node *temp = NULL;
        int num;
        cin >> num;
        temp = new node(num);
        if (head == NULL) {
            head = temp;
            t = temp;
            continue;
        }
        if (t->next == NULL)
            t->next = temp;
        t = temp;
    }
    return head;
}

// This function is used to find the mid element of the linked list.
node* findMid(node* head) {
    node* slow = head;          //Initialize two pointers, `slow` and `fast`, to the beginning of the linked list (`head`).
                                //`slow` initially points to the first node.
    node* fast = head -> next;  //`fast` initially points to the second node (if it exists).
    
    while(fast != NULL && fast -> next != NULL) {   //Enter a loop that continues as long as both `fast` and `fast->next` 
                                                    // are not NULL.
        slow = slow -> next;                        //In each iteration of the loop:
                                                    // Move the `slow` pointer one step forward by setting `slow = slow->next`. 
                                                    // This means `slow` moves one node at a time.
        fast = fast -> next -> next;                // Move the `fast` pointer two steps forward by setting `fast = fast->next->next`. 
                                                    // This means `fast` moves two nodes at a time, effectively twice as fast as `slow`. 
    }
                                                    // When the loop exits, it means that `fast` has either reached the end of the 
                                                    // list (if the list has an even number of nodes) or is one step away from the 
                                                    // end of the list (if the list has an odd number of nodes). In either case, 
                                                    // `slow` will be pointing to the middle node of the linked list.
    return slow;                                    // Finally, return the `slow` pointer, which now points to the middle element of 
                                                    // the linked list.
}

node* merge(node* left, node* right) {
    if(left == NULL)                //If `left` is NULL, it means that the left list is empty, so you can directly return `right` 
                                    // as the merged result.
        return right;
    if(right == NULL)               //If `right` is NULL, it means that the right list is empty, so you can directly return `left` 
                                    // as the merged result.
        return left;
    
    node* ans = new node(-1);       //Create a dummy node `ans` with a data value of -1 and a pointer `temp` pointing to it. 
                                    // This dummy node serves as the starting point of the merged list.
    node* temp = ans;               //temp is used to add all new nodes.
    
    //merge 2 sorted Linked List
    while(left != NULL && right != NULL) {      //Enter a loop that continues as long as both `left` and `right` are not NULL.
        if(left -> data < right -> data ) {     //If `left->data` is less than `right->data`, append the node from `left` to 
                                                // the merged list, and update `temp` and `left` pointers accordingly.
            temp -> next = left;
            temp = left;
            left = left -> next;
        }else{                                 //If `right->data` is less than or equal to `left->data`, append the node from `right` 
                                               // to the merged list, and update `temp` and `right` pointers accordingly.
            temp -> next = right;
            temp = right;
            right = right -> next;
        }
    }
                                            //After exiting the loop, there might be some remaining elements in either `left` or 
                                            // `right`.
    while(left != NULL) {                   //If there are remaining elements in `left`, append them to the merged list.
        temp -> next = left;                
        temp = left;
        left = left -> next;
    }
    
    while(right != NULL) {                 //If there are remaining elements in `right`, append them to the merged list.
        temp -> next = right;
        temp = right;
        right = right -> next;
    }
    ans = ans -> next;                     //Remove the dummy node `ans` from the beginning of the merged list by setting 
                                           // `ans = ans->next`. This step is necessary because the dummy node was used to 
                                           // simplify the merging process but is not part of the final merged list.
    return ans;                            //Return `ans`, which now points to the head of the merged sorted linked list.
}


node* mergeSort(node *head) {
    //base case
    if( head == NULL || head -> next == NULL ) {        //If the head of the linked list is NULL or the next pointer is pointing 
                                                        // to NULL that says that the linked list is already sorted so we return 
                                                        // the head back.
        return head;
    }
    
    // break linked list into 2 halvs, after finding mid
    node* mid = findMid(head);      //The findMid function is used to find the middle element of the linked list, so that 
                                    // we can then break the linked list in two halves to perform the merge sort.
    
    node* left = head;              //The left pointer is pointing to head because in merge sort after dividing the linked list 
                                    // into two halves we need one pointer respectively to point to the two linked list formed 
                                    // so that we can perform the sorting.
    node* right = mid->next;        //The right pointer points to the first element of the second part of linked list which was 
                                    // formed after breaking the linked list into two halves.
    mid -> next = NULL;             //Here mid->next is pointing to null because it is the last element of the first part of the 
                                    // broken linked list and it should point to null indicating end of the list.
    
    //recursive calls to sort both halves
    left = mergeSort(left);         //Now recursively calling the mergeSort function for the left/first broken part of linked list.
    right = mergeSort(right);       //Later recursively calling the mergeSort function for the right/second broken part of linked list.
    
    //merge both left and right halves
    node* result = merge(left, right);      //After seperating all the linked list elements now its time to sort them by comparing 
                                            // each and every linked list element.
    
    return result;      //Finally returning the sorted linked list.
}

//  Test Cases:
// enter the no. of nodes : 5
// 8 9 3 1 4
// Original Linked-list is-> 8 9 3 1 4
// Sorted Linked-list is-> 1 3 4 8 9

// enter the no. of nodes : 3
// -1 -2 -3
// Original Linked-list is-> -1 -2 -3
// Sorted Linked-list is-> -3 -2 -1

// enter the no. of nodes : 8
// 8 7 6 5 4 3 2 1
// Original Linked-list is-> 8 7 6 5 4 3 2 1
// Sorted Linked-list is-> 1 2 3 4 5 6 7 8

// enter the no. of nodes : 6
// 5 3 4 1 -2 -4
// Original Linked-list is-> 5 3 4 1 -2 -4
// Sorted Linked-list is-> -4 -2 1 3 4 5

int main() {
    node *head = NULL;
    int n;
    cout << "enter the no. of nodes : ";  // taking input from user about the
                                          // number of nodes in linked list
    cin >> n;
    if (n == 0)
        return 0;
    head = createlist(n);  // creating the list
    cout << "Original Linked-list is->";
    print(head);                          // printing the original linked list
    head= mergeSort(head);  // applying merge sort
    cout << "Sorted Linked-list is->";
    print(head);  // printing the sorted linked list
    return 0;
}