#include<iostream>
#include<list>
using namespace std;

struct ll{
      string data;
      struct ll *next;
};

void append(struct ll **node, string data)
{
      struct ll *temp = new ll;
      struct ll *last = *node;
      temp->data = data;
      temp->next = NULL;
      if (*node == NULL){
            *node = temp;
            return;
      }
      while (last->next!=NULL){
            last = last->next;
      }
      last->next = temp;
}

void display_list(struct ll *node)
{
      while(node!=NULL)
      {
            cout<<node->data<<" ";
            node = node->next;
      }
}

void pop(struct ll **node, int pos)
{
      int len=0;
      if(*node == NULL)
      {
            cout<<"NO ELMENT"<<endl;
            return;
      }
      struct ll *temp = *node;
      while (temp->next != NULL)
      {
            temp = temp->next;
            len++;
      }
      len++;
      struct ll *prev = *node;
      temp = prev->next;
      if (len==pos)
      {
            *node = prev->next;
            free(prev);
      }
      else
      {
            for (int i=1; i<(len-pos); i++)
            {
                  prev = prev->next;
                  temp = temp->next;
            }
      prev->next = temp->next;
      }
      if(pos==1)
            cout<<"1st ";
      else if(pos==2)
            cout<<"2nd ";
      else if(pos==3)
            cout<<"3rd ";
      else
            cout<<pos<<"th ";
      cout<<"element from the back deleted\n";
      //display_list(*node);
}
int main()
{
      struct ll *head = NULL;
      string el;
      string choice;
      cout<<"Write Y to continue adding number else write N to stop"<<endl;
      while(choice!="n" || choice!="N")
      {
            cin>>el;
            //cout<<el<<" | ";
            append(&head, el);
            cin>>choice;
            //cout<<choice<<", ";
            if(choice == "n" || choice=="N")
                  break;
      }
      cout<<"Positions from last remove that number: "<<endl;
      display_list(head);
      cout<<endl;
      int pos;
      for (; cin>>pos; ) {
            pop(&head, pos);
      }
      cout<<"winner is - ";
      display_list(head);
}
