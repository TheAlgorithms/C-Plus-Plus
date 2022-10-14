#include <iostream>
#include <unordered_map>
using namespace std;

class Node {
 public:
    int data;
    Node *next;
    Node *arb;
    Node(int d) {
        data = d;
        next = NULL;
        arb = NULL;
    }
};

void insertionHead(Node *&head, int d) {
    Node *temp = new Node(d);
    temp->next = head;
    head = temp;
}
void insertionTail(Node *&tail, int d) {
    Node *temp = new Node(d);
    tail->next = temp;
    tail = tail->next;
}
void print(Node *&head) {
    Node *temp = head;
    while (temp != NULL) {
        /* code */
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void insertionAtTail(Node *&head, Node *&tail, int d) {
    Node *newNode = new Node(d);
    if (head == NULL) {
        head = newNode;
        tail = newNode;
        return;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void *copyList(Node *&head) {
    // step1: create clone of original linked list
    Node *cloneHead = NULL;
    Node *cloneTail = NULL;

    Node *temp = head;
    while (temp != NULL) {
        /* code */
        insertionAtTail(cloneHead, cloneTail, temp->data);
        temp = temp->next;
    }
    // step 2 create a map

    unordered_map<Node *, Node *> mapping;
    Node *originalNode = head;
    Node *cloneNode = cloneHead;
    while (originalNode != NULL) {
        mapping[originalNode] = cloneNode;
        originalNode = originalNode->next;
        cloneNode = cloneNode->next;
    }
    originalNode = head;
    cloneNode = cloneHead;

    while (originalNode != NULL) {
        /* code */
        cloneNode->arb = mapping[originalNode->arb];
        originalNode = originalNode->next;
        cloneNode = cloneNode->next;
    }
    return cloneHead;
}

int main() {
    Node *node1 = new Node(20);

    Node *head = node1;
    Node *tail = node1;
    // print(head);
    // insertion at headddd
    insertionHead(head, 18);
    insertionHead(head, 16);
    insertionHead(head, 14);
    insertionHead(head, 12);
    // print(head);
    // INsertion at tailll
    insertionTail(tail, 22);
    insertionTail(tail, 24);
    insertionTail(tail, 26);
    insertionTail(tail, 28);
    print(head);

    cout << copyList(head) << endl;

    return 0;
}