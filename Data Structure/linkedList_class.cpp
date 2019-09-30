#include <iostream>

using namespace std;

struct node{
    int data;
    node* next;
};

class linkedList{
protected:
    node* head;
public:
    linkedList(){
        head = NULL;
    }
    void insertFirst(int x){
        // inserting at the beginning of the linked list.
        node* temp = new node();
        temp->data = x;
        temp->next = head;
        head = temp;
    }
    void insertLast(int x){
        // inserting at the end of the linked list.
        if(head == NULL) cout << "The list is empty.\n";
        else {
            node* temp = head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            node *temp2 = new node();
            temp2->data = x;
            temp2->next = NULL;
            temp->next = temp2;
        }
    }
    void insertAt(int x, int n){
        // inserting at the nth position of the linked list.
        if(n == 1){
            node* temp = new node();
            temp->data = x;
            temp->next = head;
            head = temp;
        }
        else{
            node* temp = head;
            while(n > 1 && temp->next != NULL){
                temp = temp->next;
                n--;
            }
            node* temp2 = new node();
            temp2->data = x;
            temp2->next = temp->next;
            temp->next = temp2;
        }
    }
    void printList(){
        // printing the linked list.
        if(head == NULL) cout << "The list is empty.\n";
        else{
            node* temp = head;
            while(temp != NULL){
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
    void deleteNode(int n){
        // deleting the node at nth position.
        node* temp = head;

        if(head == NULL) cout << "List is empty.\n";

        else if(n == 1){
            // while deleting element at first position.
            temp = temp->next;
            delete head;
            head = temp;
            cout << "Element deleted.\n";
        }

        else{
            while(n > 1 && temp->next != NULL){
                temp = temp->next;
                n--;
            }
            if(n > 1){
                cout << "Invalid position.\n";
            }
            else if(temp->next == NULL){
                // while deleting last element.
                node* temp2 = temp;
                temp = temp->next;
                delete temp;
                temp2->next = NULL;
                cout << "Element deleted.\n";
            }
            else{
                // while deleting element at nth position.
                temp = temp->next;
                delete temp;
                cout << "Element deleted.\n";
            }
        }
    }
    void reverseList(){
        /* NOTE:- I've already used 'next' as the name for the pointer to next node, so here to avoid confusion, I've use 
         * the Hindi names for previous(i.e. pichla), this(i.e. yeh) and next(i.e. agla)
         */ 
        node *pichla, *yeh, *agla;
        pichla = NULL; yeh = head; agla = yeh->next;
        while(agla!=NULL){
            yeh->next = pichla;
            pichla = yeh;
            yeh = agla;
            agla = yeh->next;
        }
    }
    void search(int x){
        // searching the linked list for element x.
        int pos = 1;
        node* temp = head;
        while(temp != NULL){
            if(temp->data==x) { cout << "Found " << x << " at position " << pos << ".\n"; return; }
            cout << temp->data << " ";
            temp = temp->next;
            pos++;
        }
        cout << x << " not found in linked list.\n";
    }
};


int main(){
    linkedList list1;
    list1.insertFirst(2);   //list: 2
    list1.insertFirst(1);   //list: 1 2
    list1.insertAt(3, 3);   //list: 1 2 3
    list1.printList();      //list: 1 2 3
    list1.deleteNode(1);    //list: 2 3
    list1.printList();      //list: 2 3
    list1.search(2);        //list: 2 3
    list1.search(0);        //list: 2 3
    list1.insertFirst(0);   //list: 0 2 3
    list1.printList();      //list: 0 2 3
    list1.reverseList();    //list: 3 2 0
    list1.printList();      //list: 3 2 0
}