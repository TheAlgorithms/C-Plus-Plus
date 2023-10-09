// in this code i will show you how to take input from user in linked list in better optimised ways.
// @aivnash


//1st way is naive approch

Node *takeInput() {
    int data; // Variable to store the input data.
    cin >> data; // Read the first input data.

    Node *head = NULL; // Initialize the head of the linked list to NULL.

    // Continue reading input data until -1 is encountered.
    while (data != -1) {
        // Create a new Node with the current data.
        Node *newNode = new Node(data);

        // If the linked list is empty, set the new node as the head.
        if (head == NULL) {
            head = newNode;
        } else {
            // If the linked list is not empty, traverse to the end and add the new node there.
            Node *temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }

        // Read the next input data.
        cin >> data;
    }

    // Return the head of the linked list.
    return head;
}
//Complexity analysis - this code has time complexity of O(N^2)
/*





*/
// Lets see the better and optimised approch

Node* takeInput_better() {
    int data; // Variable to store the input data.
    cin >> data; // Read the first input data.

    Node* head = NULL; // Initialize the head of the linked list to NULL.
    Node* tail = NULL; // Initialize the tail of the linked list to NULL.

    // Continue reading input data until -1 is encountered.
    while (data != -1) {
        // Create a new Node with the current data.
        Node* newNode = new Node(data);

        // If the linked list is empty, set both head and tail to the new node.
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            // If the linked list is not empty, append the new node to the tail and update the tail pointer.
            tail->next = newNode;
            tail = tail->next;
        }

        // Read the next input data.
        cin >> data;
    }

    // Return the head of the linked list.
    return head;
}


// Time complexity of this code is O(n)




