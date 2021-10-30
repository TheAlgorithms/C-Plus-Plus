#include <iostream>
using namespace std;

struct node {
    int val;
    node *next;
};

node *start;

void insert(int x) {
    node *t = start;
    if (start != NULL) {
        while (t->next != NULL) {
            t = t->next;
        }
        node *n = new node;
        t->next = n;
        n->val = x;
        n->next = NULL;
    } else {
        node *n = new node;
        n->val = x;
        n->next = NULL;
        start = n;
    }
}


void show() {
    node *t = start;
    while (t != NULL) {
        cout << t->val << "\t";
        t = t->next;
    }
    cout<<"\n";
}
     void printMiddle(node *head)
     {
        struct node *slow_ptr = head;
        struct node *fast_ptr = head;
  
        if (head!=NULL)
        {
            while (fast_ptr != NULL && fast_ptr->next != NULL)
            {
                fast_ptr = fast_ptr->next->next;
                slow_ptr = slow_ptr->next;
            }
            cout << "The middle element is [" << slow_ptr->val << "]" << endl;
        }
    }


int main() {
    insert(1);
    insert(2);
    insert(3);
    insert(4);
    insert(5);
    
    show();
    printMiddle(start);

    return 0;
}
