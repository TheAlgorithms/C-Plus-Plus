#include<bits/stdc++.h>
using namespace std;

class CQueue
{
  public:
  int *array,Size;
  int front,back;
  CQueue(int size)
  {
    Size=size;array= new int[size];
    front = back = –1;
  }

int isFull()
{
    if((front==back+1)||(front == 0 &&back== Size– 1))
        return 1;
    return 0;
}
int isEmpty()
{
    if (front == –1) return 1;
  return 0;
}

void enqueue(int value)
{
    cout<<“Pushing the value : “<<value<<endl;
    if (isFull())
        cout<<“Can not push “<<value<<“, The Circular Queue is Full.”<<endl;
    else
    {
        if (front == –1) front = 0;
        back = (back + 1) % Size;
        array[back] = value;
  }
}

int dequeue()
{
  int element;
  if (isEmpty()) {
    cout<<“The Circular Queue is empty.”<<endl;
    return –1;
  }
    element = array[front];
    if (front ==back) {
      front = –1;
      back = –1;
    }

    else {
      front = (front + 1) % Size;
    }
    cout<<“Popping out the value : “<<element<<endl;
    return element;
  
}

void Show(){
    int i;
    if (isEmpty()) cout<<“The Circular Queue is empty.”<<endl;
    else
    {
        cout<<“The Circular Queue is :”<<endl;
        for (i=front; i!=back;i= (i+1)%Size)
            cout<<array[i]<<” “;
    cout<<array[i]<<endl;
  }
}
};

int main() {

  CQueue CQ(6);
  CQ.enqueue(2);CQ.enqueue(7);
  CQ.enqueue(3);CQ.enqueue(9);
  CQ.Show();
  CQ.enqueue(8);CQ.enqueue(4);
  CQ.enqueue(1);
  CQ.dequeue();
  
  CQ.enqueue(10);CQ.dequeue();
  CQ.Show();

  return 0;
}
