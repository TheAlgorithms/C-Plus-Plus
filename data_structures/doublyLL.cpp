/*____Garg's Code_____*/
#include <bits/stdc++.h>
using namespace std;

template<class T>
class Node
{
  public:
    Node *prev, *forv;
    T info;
};

template<class T>
class DoublyLL
{
  public:
    Node<T> *start;

    DoublyLL()
    {
      start = NULL;
    }

    void push(T no)
    {
      Node<T> *new_node = new Node<T>;
      Node<T> *new_next = new Node<T>;
      Node<T> *new_back = new Node<T>;
      if(new_node == NULL)
      {
        cout << "Memory Limit Exceeded!\n";
        return;
      }
      new_node->info = no;
      new_node->forv = NULL;
      new_node->prev = NULL;
      if(start == NULL)
      {
        
        new_node->forv = NULL;
        new_node->prev = NULL;
        start = new_node;
      }
      else
      {
        new_back = NULL;
        new_next = start;
        if(start->info >= no)
        {
          new_node->prev = NULL;
          new_node->forv = start;
          start->prev = new_node;
          start = new_node;
          return;
        }
        while(new_next != NULL and new_next->info < no)
        {
          new_back = new_next;
          new_next = new_next->forv;
        }

        if(new_next == NULL)
        {
          new_back->forv = new_node;
          new_node->prev = new_back;
          new_node->forv = NULL;
        }
        else
        {
          new_back->forv = new_node;
          new_node->prev = new_back;
          new_node->forv = new_next;
          new_next->prev = new_node;
        }  
      }
    }

    void show_list()
    {
      Node<T> *new_node = new Node<T>;
      new_node = start;
      cout << "START -> ";
      while(new_node != NULL)
      {
        cout << new_node->info << " <-> ";
        new_node = new_node->forv;
      }
      cout << "NULL";
    }  
};
  
int main()
{
 
  DoublyLL<int> st;

  st.push(1); 
  st.push(-1);
  st.push(0);
  st.push(2);
  st.push(15);
  st.push(-2);
  st.push(7);
  st.show_list();



  return 0;
}
