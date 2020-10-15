/*____Garg's Code_____*/
#include <iostream>

using namespace std;

//Create a template class for Linked List implementation of stack
template<class T>
class Node
{
  public:
    Node *link;
    T info;
};

//Declaration of class Stack
template<class T>
class Stack
{
  public:
    //Define three stacks one containing minimum element, one with maximum element and one with stack values
    Node<T> *maxm, *minm;
      
    T top, maximum, minimum;
    int size;
    Node<T> *start;
    //Constructor for stack class
    Stack()
    {
      maxm = NULL;
      minm = NULL;
      size = 0;
      start = NULL;
    }
    //Function for push operation
    void push(T no)
    {
      Node<T>* new_node = new Node<T>;
      if(new_node == NULL)
      {
        cout << "Stack Overflow\n";
      }
      Node<T> *new_max = new Node<T>;
      Node<T> *new_min = new Node<T>;
      new_node->info = no;

      if(size == 0)
      {
        new_node->link = NULL;
        start = new_node;
        maxm = new_node;

        minm = new_node;
      }
      else
      {
        new_node->link = start;
        start = new_node;
        new_max->info = max(no, maxm->info);
        new_max->link = maxm;
        maxm = new_max;
        new_min->info = min(no, minm->info);
        new_min->link = minm;
        minm = new_min;
      }
      maximum = maxm->info;
      minimum = minm->info;
      size++;
      top = no;
    }
    //Function for pop operation
    void pop()
    {
      Node<T> *new_node = new Node<T>;

      if(size == 0)
      {
        cout << "Stack Underflow\n";
        return;
      }
      new_node = start;
      start = new_node->link;
      top = start->info;
      delete new_node;

      Node<T> *new_max = new Node<T>;
      new_max = maxm;
      maxm = new_max->link;
      maximum = maxm->info;
      delete new_max;

      Node<T> *new_min = new Node<T>;
      new_min = minm;
      minm = new_min->link;
      minimum = minm->info;
      delete new_min;

      size--;
    }
    void show_top()
    {
      if(size == 0)
      {
        cout << "Nothing to show, stack is empty!\n";
      }
      else
      {
        cout << top << endl;
      }
    }
    void show_max()
    {
      if(size == 0)
      {
        cout << "Nothing to show, stack is empty!\n";
      } 
      else
      {
        cout << maximum << endl;
      }
    }
    void show_min()
    {
      if(size == 0)
      {
        cout << "Nothing to show, stack is empty!\n";
      } 
      else
      {
        cout << minimum << endl;
      } 
    }
};
  
int main()
{
  Stack<int> st;
  st.push(1);
  st.push(2);
  st.push(3);
  st.push(4);
  st.push(5);
  st.pop();
  st.pop();
  st.show_top();
  st.show_max();
  st.show_min();



  return 0;
}
