#include <iostream>
using namespace std;
template<class T>class node
{
public:
 T info;
 node<T> *next,*prev;
 node()
 {
 prev = 0;
 next = 0;
 }
 node(T x, node<T> *n = 0, node<T> *p = 0)
 {
 info = x;
 next = n;
 prev = p;
 }
};
template<class T>class dllist
{
private:
 node<T> *head;
 node<T> *tail;
public:
 dllist()
 {
 head = tail = 0;
 }
 int isempty();
 void addtohead(T x);
 void addtotail(T x);
 void add_at_i(int i, T x);
 T delete_fromhead();
 T delete_fromtail();
 void deletenode(T x);
 void length();
 void delete_from_i(int i);
 T isinlist(int x);
 void concat(dllist<T> L1);
 void reverse(dllist<T> L1);
 dllist operator + (dllist<T> L1);
 T input();
 void display();
};
template<class T>int dllist<T> :: isempty()
{
 if(head == 0 && tail == 0)
 return 1;
 else
 return 0;
}
template<class T>void dllist<T> :: addtohead(T x)
{
 node<T> *temp = new node<T>(x);
 if(isempty())
 {
 head = tail = temp;
 }
 else
 {
 temp -> next = head;
 head -> prev = temp;
 head = temp;
 }
}
template<class T>void dllist<T> :: addtotail(T x)
{
 node<T> *temp = new node<T>(x);
 if(isempty())
 {
 head = tail = temp;
 }
 else
 {
 tail -> next = temp;
 temp -> prev = tail;
 tail = temp;
 }
}
template<class T>void dllist<T> :: add_at_i(int i,T
x)
{
 if(i < 0)
 {
 cout<<"Out of bound !"<<endl;
 return;
 }
 node<T> *nptr = new node<T>[1];
 nptr -> info = x;
 int count = 0;
 node<T> *temp = head;
 while(temp != NULL && count < i)
 {
 if(count == i-1)
 {
 if(temp -> next != NULL)
 {
 nptr -> next = temp -> next;
 }
 temp -> next = nptr;
 nptr -> prev = temp;
 cout<<"New Node added at ith position"<<i<<" !"<<endl;
 break;
 }
 count++;
 temp = temp -> next;
 }
}
template<class T>void dllist<T> :: length()
{
 int len = 0;
 node<int> *temp = head;
 while(temp != NULL)
 {
 len++;
 temp = temp -> next;
 }
 return;
}
template<class T>T dllist<T> :: delete_fromhead()
{
 T x = head -> info;
 if(head == tail)
 {
 delete head;
 head = tail = 0;
 }
 else
 {
 head = head -> next;
 delete head -> prev;
 head -> prev = 0;
 }
 return x;
}
template<class T>T dllist<T> :: delete_fromtail()
{
 T x = tail -> info;
 if(head == tail)
 {
 delete head;
 head = tail = 0;
 }
 else
 {
 tail = tail -> prev;
 delete tail -> next;
 tail -> next = 0;
 }
 return x;
}
template<class T>void dllist<T> :: delete_from_i(int
i)
{
 if(head == NULL)
 {
 cout<<"Linked List is Empty !"<<endl;
 return;
 }
 if(i < 0)
 {
 cout<<"Out of bound !"<<endl;
 return;
 }
 if(i == 0)
 {
 delete_fromhead();
 cout<<"Node removed from ith position"<<i<<endl;
 return;
 }
 int count = 0;
 node<T> *temp = head;
 while(temp != NULL)
 {
 if(count == i-1)
 {
 temp -> next = temp -> next -> next;
 cout<<"Node removed from ith position"<<i<<endl;
 break;
 }
 count++;
 temp = temp -> next;
 }
}
template<class T>void dllist<T> :: display()
{
 node<T> *temp = head;
 cout<<endl<<"_Doubly Linked List is ";
 while(temp != NULL)
 {
 cout<<temp -> info<<" ";
 temp = temp -> next;
 }
}
template<class T>T dllist<T> :: input()
{
 T n;
 cout<<"***Please Enter the Number*** : ";
 cin>>n;
 return n;
}
template<class T>void dllist<T> :: deletenode(T x)
{
 node<T> *temp,*prev;
 if((head == tail) && (head -> info == x))
 {
 delete head;
 head = tail = 0;
 }
 else if(head -> info == x)
 {
 head = head -> next;
 delete head -> prev;
 head -> prev = NULL;
 cout<<"node"<<x<<"has been deleted from your list";
   }
 else
 {
 prev = head;
 temp = head -> next;
 while((temp != 0) && (temp -> info != x))
 {
 prev = temp;
 temp = temp -> next;
 }
 if(temp != 0)
 {
 prev -> next = temp -> next;
 if(temp == tail)
 tail = prev;
 delete temp;
 }
 else
 {
 cout<<"Elements not found "<<endl;
 }
 }
}
template<class T>T dllist<T> :: isinlist(int x)
{
 node<T> *temp;
 if(head -> info == x)
 {
 return 1;
 }
 else if(tail -> info == x)
 return 1;
 else
 {
 temp = head;
 while((temp != 0) && (temp -> info != x))
 {
 temp = temp -> next;
 }
 if(temp != 0)
 return 1;
 else
 return 0;
 }
 return 0;
}
template<class T>void dllist<T> :: reverse(dllist<T>
L1)
{
 node<T> *temp;
 temp = L1.head;
 while(temp != 0)
 {
 (*this).addtohead(temp -> info);
 temp = temp -> next;
 }
 display();
}
template<class T>void dllist<T> :: concat(dllist<T>
L1)
{
 node<T> *temp;
 temp = L1.head;
 while(temp != 0)
 {
 (*this).addtotail(temp -> info);
 temp = temp -> next;
 }
 (*this).display();
}
template<class T>dllist<T>dllist<T> :: operator +
(dllist<T> L1)
{
 node<T> *temp;
 dllist L3;
 if(!(*this).isempty());
 {
 temp = (*this).head;
 while(temp != 0)
 {
 L3.addtotail(temp -> info);
 temp = temp -> next;
 }
 if(!L1.isempty())
 {
 temp = L1.head;
 while(temp!=0)
 {
 L3.addtotail(temp -> info);
 temp = temp -> next;
 }
 }
 return L3;
 }
}
int main()
{
 dllist<int> L1,L2,L3;
 char c = 'y';
 int choice, x, s, num , a;
 while(c=='y'||c=='Y')
 {
 cout<<"***Have a look at the Main Menu***"<<endl;
 cout<<" 1. Add To Head "<<endl;
 cout<<" 2. Add To Tail "<<endl;
 cout<<" 3. Add at ith position "<<endl;
 cout<<" 4. Delete From Head "<<endl;
 cout<<" 5. Delete From Tail "<<endl;
 cout<<" 6. Delete from ith position "<<endl;
 cout<<" 7. Delete The Node From Doubly Linked List "<<endl;
 cout<<" 8. Find The Node in Doubly Linked List "<<endl;
 cout<<" 9. To Reverse The Element "<<endl;
 cout<<" 10. To concatenate the Elements in Doubly Linked List "<<endl;
 cout<<" 11. To Display The Doubly Linked List "<<endl;

cout<<"**********************************************"<<endl;
 cout<<"Enter your Choice : ";
 cin>>choice;
 switch(choice)
 {
 case 1: x= L1.input();
 L1.addtohead(x);
 L1.display();
 break;
 case 2: x= L1.input();
 L1.addtotail(x);
 L1.display();
 break;
 case 3: x= L1.input();
 cout<<"Enter the ith position where the new node to be inserted :";
 cin>>a;
 cout<<"Enter the No. which you inserted at the very starting : ";
 cin>>num;
 L1.add_at_i(a, num);
 L1.display();
 break;
 case 4: if(!L1.isempty())
 {
 s = L1.delete_fromhead();
 cout<<"Deleted Node is : "<<s;
  L1.display();
 }
 else
 {
 cout<<"The List is Empty !";
 }
 break;
 case 5: if(!L1.isempty())
 {
 s = L1.delete_fromtail();
 cout<<"Deleted node is : "<<s;
 L1.display();
 }
 else
 {
 cout<<"The List is Empty !";
 }
 break;
 case 6: if(!L1.isempty())
 {
 cout<<"Enter the index : ";
 cin>>a;
 L1.delete_from_i(a);
 L1.display();
 }
 else
 {
 cout<<"List is empty!";
 }
 break;
 case 7: if(!L1.isempty())
 {
 cout<<"Enter the value which you want to delete : ";
 cin>>x;
 L1.deletenode(x);
 L1.display();
 }
 else
 {
 cout<<"List is empty!";
 }
 break;
 case 8: if(!L1.isempty())
 {
 cout<<"Enter the Value which you want to Search : ";
 cin>>x;
 s = L1.isinlist(x);
 if(s == 1)
 cout<<" We have found the Node you Searched For !!! ";
 else
 cout<<" Sorry ! The Node you searched for is not found ";
 }
 else
 {
 cout<<"The List is Empty ";
 }
 break;
 case 9: if(!L1.isempty())
 {
 L2.reverse(L1);
 }
 else
 {
 cout<<"List is empty ";
 }
 break;
 case 10: if((L1.isempty()) &&
(L2.isempty()))
 {
 cout<<"The List is Empty";
 }
 else
 {
 L2.concat(L1);
 cout<<"Concatenated List is :";
 L2.display();
 }
 break;
 case 11: L3 = L1 + L2;
 L3.display();
 break;
 default: cout<<"Error in input"<<endl;
 }
 cout<<endl;
 cout<<"Do u want to continue(y/n): ";
 cin>>c;
 }
return 0;
}
