#include <iostream>
using namespace std;
// searching in a sorted linked list
class node {
 public:
    int info;
    node* link;
};
node* search(int, node*);
int main() {
    int n, x, i = 1;
    cin >> n;
    node* start;
    node* ptr;
    node* temp;
    start = new node;
    start->info = 19;
    ptr = start;
    while (i < n - 1) {
        temp = new node;
        cin >> x;
        temp->info = x;
        ptr->link = temp;
        ptr = temp;
        i++;
        // cout<<"moving to"<<i<<endl;
    }
    // cout<<"here1";
    temp = new node;
    cin >> x;
    temp->info = x;
    // cout<<"here2";
    ptr->link = temp;
    temp->link = NULL;
    // searching a sorted array
    int item;
    cin >> item;
    cout << "item found at" << search(item, start) << endl;
    return 0;
}
node* search(int item, node* start) {
    node* ptr;
    ptr = start;
    while (item <= ptr->info) {
        if (item == ptr->info)
            return ptr;
        else
            ptr = ptr->link;
    }
    return NULL;
}
