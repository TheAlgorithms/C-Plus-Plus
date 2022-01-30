#include <iostream>
class LinkedList {
 public:
    struct Node {
        Node* next = nullptr;
        Node* prev = nullptr;
        int value = 0;
    };

    Node* findMiddle();
    void addNode(int value);

 private:
    Node* tail = nullptr;
    Node* head = nullptr;
    Node* middle = nullptr;
};

void LinkedList::addNode(const int value) {
    Node* newNode = new Node();
    newNode->value = value;
    if (head == nullptr) {  // first node (head) is null. Linked list is empty.
        head = newNode;
        tail = newNode;
        // head and tail are the same node when there is only one node in list
    } else {                   // head is not null. Linked list contains nodes.
        newNode->prev = tail;  // tail is the previous node to newNode, which
                               // will be the new tail
        tail->next = newNode;  // newNode is next after tail
        tail = newNode;        // newNode is now the tail
    }

    // std::cout << "Inserting node with value " << value << std::endl;
}

LinkedList::Node* LinkedList::findMiddle() {
    // Prints value of middle node in linked list using two pointer approach
    // (slow and fast)
    Node* slow = head;
    Node* fast = head;
    if (head != nullptr) {
        while (fast != nullptr && fast->next != nullptr) {
            // fast and its next pointer are not null
            fast = fast->next
                       ->next;  // fast pointer advances two nodes per iteration
            slow = slow->next;  // slow pointer advances one node per iteration
        }

        // the slow pointer will be at the middle of the linked list once the
        // fast pointer reaches the end.

        std::cout << "Middle element of linked list: " << slow->value
                  << std::endl;
        return slow;
    } else {
        std::cout << "Linked list is empty." << std::endl;
        return nullptr;
    }
}

static void test() {
    auto linked = new LinkedList();
    LinkedList::Node* middle = linked->findMiddle();  // Linked list is empty.
    if (middle != nullptr) {
        std::cout << "middle should be nullptr, linked list is empty"
                  << std::endl;
    }
    int numElements = 42;
    std::cout << "Inserting nodes..." << std::endl;
    for (int i = 1; i < numElements;
         i++) {  // insert nodes to populate linked list
        linked->addNode(i);
    }

    middle = linked->findMiddle();
    if (numElements % 2 == 0) {
        // even number of elements
        if (middle->value == numElements / 2) {
            std::cout << "Test passed." << std::endl;
        } else {
            std::cout << "Test failed." << std::endl;
        }
    } else {
        // odd number of elements
        if (middle->value == (numElements + 1) / 2) {
            std::cout << "Test passed." << std::endl;
        } else {
            std::cout << "Test failed." << std::endl;
        }
    }
}

int main() {
    test();
    return 0;
}