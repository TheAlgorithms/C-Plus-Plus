#include <iostream>
using namespace std;

struct node{
    string value;
    node *next, *prev;
};

node *head, *tail;

void Enqueue(string x){
    if (tail == nullptr) {
        node *n = new node;
        n->value = x;
        n->next = nullptr;
        n->prev = nullptr;
        tail = n;
        head = n;
    }

    else {
        node *n = new node;
        n->value = x;
        n->next = nullptr;
        n->prev = tail;
        tail->next = n;
        tail = n;
    }
}

void Dequeue() {
    if (tail == nullptr && head == nullptr) {
        cout << "\nQueue is empty";
    }
    else {
        node *t = head;
        cout << "\n" << t->value << " deleted";
        head = head->next;
        if(head != nullptr){
            head->prev = nullptr;
        }
        delete t;
        if (head == nullptr)
            tail = nullptr;
    }
}

void Forward() {
    node *t = head;
    while (t != nullptr) {
        cout << t->value << " ";
        t = t->next;
    }
}

void Reverse() {
    node *t = tail;
    while (t != nullptr) {
        cout << t->value << " ";
        t = t->prev;
    }
}

void Size(){
    node *t = head;
    if (head == nullptr){
        cout << "There are 0 items in queue.";
        return;
    }
    int count = 0;
    while (t != nullptr) {
        t = t->next;
        count++;
    }
    cout << "There are " << count << " item(s) in queue.";
}

int main() {
    int ch = 1;
    string x = "";
    while (ch != 0){
        cout << "\n1. Enqueue";
        cout << "\n2. Dequeue";
        cout << "\n3. Print forward";
        cout << "\n4. Print backward";
        cout << "\n5. Queue size";
        cout << "\nEnter Your Choice :";
        cin >> ch;
        switch(ch){
            case 1:
                cout << "Insert : ";
                cin >> x;
                Enqueue(x);
                continue;
            case 2:
                Dequeue();
                continue;
            case 3:
                Forward();
                continue;
            case 4:
                Reverse();
                continue;
            case 5:
                Size();
                continue;
            default:
                cout << "That wasn't an option, try again.";
                continue;
        }
    }
    return 0;
}
