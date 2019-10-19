/*
*
*   A Dynamic Linked List is a type of linked list where unlimited data can be entered without specifying it in the beginning.\
*
*
*/


#include <iostream>
using namespace std;

class Node
{
    public:
    int data;
    Node *next;
};

main() {
    Node *temp = new Node();
    Node *first = NULL;

    int n;

    while(true)
    {//***
        cin >> n; 
        //Linked list creation stops if entered value is -1
        if(n < 0)
            break;

        else {
            //if first is null, linked list is not created
            if(first == NULL) {
                first = new Node();
                first->data = n;
                first->next = NULL;
            }
            else {
                for(temp = first; temp->next != NULL; temp = temp->next){
                    //temp takes us to the node that has null in its "next" part, i.e, the last node
                }
                temp->next = new Node;
                temp->next->data = n;
                temp->next->next = NULL;

            }
        }
    }//***

    if(first != NULL) {
        for(temp = first; temp != NULL; temp = temp->next) {
            cout << temp->data << "\t";
        }
    }
}


/*

Output

1
2
3
4
5
-1

1   2   3   4   5

*/
