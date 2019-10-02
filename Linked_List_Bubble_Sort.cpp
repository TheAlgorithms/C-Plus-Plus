#include <iostream>

using namespace std;

struct node
{
    int data;
    node *next;
} *head = NULL;

bool Is_List_Empty()
{
    if(head == NULL)
        return true;

    return false;
}

void Insert_At_End(int value)
{
    node *temp = new node, *current = head;
    temp -> data = value;
    temp -> next = NULL;

    if(Is_List_Empty())
    {
        head = temp;
        return ;
    }

    while(current -> next != NULL)
        current = current -> next;

    current -> next = temp;
}

void Bubble_Sort(){
  int cnt = 0;
  node *start = head;
  node *curr = NULL;
  node *trail = NULL;
  node *tmp = NULL;

  //get cnt(size) of linked list
  while(start != NULL){
    start = start->next;
    ++cnt;
  }

  for (int i = 0; i < cnt; ++i){
    //set curr and trail at the start node
    curr = trail = head;

    while(curr->next != NULL){
      //compares curr and its next
      if (curr->data > curr->next->data){

	//swaps pointers for curr & curr->next
	tmp = curr->next;
	curr->next = curr->next->next;
	tmp->next = curr;

	//setup pointers for the head and trail if applicable
	if(curr ==head)
	  head = trail = tmp;
	else
	  trail->next = tmp;

	curr = tmp;
      }
      //advance pointers
      trail = curr;
      curr = curr->next;
    }
  }
}

void Print_Linked_List()
{
    if(Is_List_Empty())
    {
        cout << "List is Empty" << endl;
        return ;
    }

    node *current = head;

    while(current -> next != NULL)
    {
        cout << current -> data << " -> ";
        current = current -> next;
    }

    cout << current -> data << endl;
}

int main()
{
    int i;

    cout << "Before Bubble Sort ";
    for(i = 10; i > 5; --i)
      Insert_At_End(i);

    Print_Linked_List();
    Bubble_Sort();
    cout << "After Bubble Sort  ";
    Print_Linked_List();

    return 0;
}

/* Output
   Before Bubble Sort 10 -> 9 -> 8 -> 7 -> 6
   After Bubble Sort  6 -> 7 -> 8 -> 9 -> 10
*/
