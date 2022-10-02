/**
 * @ linked list using template
 * @brief The linked list stores data in sequential storage, like arrays. Though the data are stored sequentially,
   the memory locations are not contiguous. Unlike an array, the linked list can store data of different data types.

 * @author Nasreen parween (https://github.com/NasreenParween)
 * @see singly_linked_list.cpp, stack_using_linked_list.cpp, circular_linked_list.cpp ,doubly_linked_listn.cpp
 */

#include<iostream>
using namespace std;

template<class T>
// Node class to represent
// a node of the linked list
struct node{
    T info;
    node<T> *next;
};

template<class t>
class linkedlist{
    public:
    node<t> *start;
    // Default constructor
    linkedlist(){
        start=NULL;
    }
    node<t>  *createnewnode(t val){
        node<t> *newnode;
        newnode=new node<t>();
        newnode->info=val;
        newnode->next=NULL;

        return (newnode);
    }
    void createnewlist(node<t> *newnode){
            node<t> *temp;
            temp=start;
            newnode->next=temp;
            start=newnode;
    }
    // Function to insert a node at the end of the linked list.
    void addatend(node<t> *newnode){
         node<t>* temp;
 if(start==NULL)
 {
 start=newnode;
 return;
 }
 for(temp=start; temp->next!=NULL; temp=temp->next)
 {
 }
 temp->next=newnode;
}
// Function to insert a after the node the linked list.
    void addafter(node<t> *newnode){
        int after;
        cout<<"Enter the info part of the node after which you want to add the new node :\n";
        cin>>after;
            node<t> *temp;
            for(temp=start;temp!=NULL;temp=temp->next){
                if(temp->info==after){
                    newnode->next=temp->next;
                    temp->next=newnode;
                }
            }
    }

    void addbefore(node<t> *newnode){
        node<t> *temp;
        int before;
        cout<<"Enter the info part of node before which you want to add the new node :\n";
        cin>>before;
        if(start->info==before){
            temp=start;
            newnode->next=temp;
            start=newnode;
            return;
        }
        else{
            for(temp=start;temp->next!=NULL;temp=temp->next){
                if(temp->next->info==before){
                    newnode->next=temp->next;
                    temp->next=newnode;
                    break;
                }
            }
        }
    }

    t deletespecific(t i){
            node<t> *temp;
            int del;
            int c;
            if(i==1){
                del=start->info;
                temp=start;
                start=start->next;
                delete temp;
                return del;
            }
            else if(i>=1){
                node<t> *p;
                for(temp=start;temp->next!=NULL;temp=temp->next){
                    ++c;
                    if(c==i-1 && temp->next->next==NULL){
                        p=temp->next;
                        temp->next=NULL;
                        del=p->info;
                        delete p;
                    }
                    else if(c==i-1){
                        p=temp->next;
                        del=p->info;
                        temp->next=temp->next->next;
                        delete p;
                    }
                }
            }
                return del;
    }
    // Function to delete the node at given position

    void deletion(){
        int d;
        cout<<"Enter the info part of the node you wish to delete: \n";
        cin>>d;
        node<t> *temp;
        if(start->info==d){
            temp=start;
            start=start->next;
            delete temp;
        }
        else{
            for(temp=start;temp->next!=NULL;temp=temp->next){
                if(temp->next->info==d){
                    node<t> *ptr=temp->next;
                    temp->next=ptr->next;
                    delete ptr;
                    break;
                }
            }
        }

    }

    int count(){
        int ct=0;
        node<t> *temp;
        for(temp=start;temp!=NULL;temp=temp->next){
            ++ct;
        }
        return ct;
    }
// Function to print the linked list.
    void display(){
        if(start==NULL){
            cout<<"List is empty \n";
            return;
        }
        else{
            node<t> *temp;
            cout<<"Contents of the LL are \n";
            for(temp=start;temp!=NULL;temp=temp->next){
                cout<<(temp->info)<<" ";
            }
            cout<<endl;
        }
    }

  linkedlist  operator+  (linkedlist l1){
        node<t> *temp;
        linkedlist l3;
        if(start!=NULL){
            temp=(*this).start;
        }
        while(temp!=NULL){
            l3.addatend(temp);
            temp=temp->next;
        }
        if(l1.start!=NULL){
            temp=l1.start;
            while(temp!=NULL){
                l3.addatend(temp);
                temp=temp->next;
            }
        }
        return l3;
    }
};

int main(){
    int choice,infos,n,c1,i;
    node<int> *nptr;
    linkedlist<int> l1,l2,l3;
    cout<<"creating new LL,enter number of nodes: \n";
    cin>>n;
    for(int i=n-1;i>=0;--i){
         cout<<"Enter info for node numbered :"<<i+1<<endl;
         cin>>infos;
         nptr=l1.createnewnode(infos);
        if(nptr==NULL){
            cout<<"compiler out of memory \n";
            exit(0);
        }
        else{
            l1.createnewlist(nptr);
        }
    }
    do
 {

 cout<<"========MAIN MENU========"<<endl;
 cout<<"0. Exit"<<endl;
 cout<<"1. ADD A NODE BEFORE :"<<endl;
 cout<<"2. ADD A NODE AFTER :"<<endl;
 cout<<"3. ADD A NODE AT LAST :" <<endl;
 cout<<"4. DELETE A NODE : "<<endl;
 cout<<"5. COUNT THE TOTAL NUMBER OF NODES : "<<endl;
 cout<<"6. DISPLAY THE LINKED LIST :"<<endl;
 cout<<"7. DELETE A NODE FROM ANY POSITION :"<<endl;
 cout<<"8. CONCATENATE 2 LIST :"<<endl;
 cout<<"============================="<<endl;
 cout<<"Enter your choice between(1-8) "<<endl;

 cin>>choice;
 switch (choice)
 {
 case 1 :
         cout<<"Enter the info part to be added \n";
          cin>>infos;
            nptr=l1.createnewnode(infos);
           if(nptr==NULL){
           cout<<"out of memory \n";
              exit(0);
             }
           else{
                l1.addbefore(nptr);
              l1.display();
              }
             break;
 case 2 :
          cout<<"Enter the info part to be added \n";
            cin>>infos;
          nptr=l1.createnewnode(infos);
          if(nptr==NULL){
          cout<<"out of memory \n";
          exit(0);
             }
           else{
          l1.addafter(nptr);
          l1.display();
              }
           break;

 case 3 :
         cout<<"Enter the info part to be added \n";
         cin>>infos;
         nptr=l1.createnewnode(infos);
        if(nptr==NULL){
           cout<<"out of memory \n";
          exit(0);
          }
           else{
           l1.addatend(nptr);
            l1.display();
             }
           break;

 case 4 :
           l1.deletion();
            l1.display();
          break;

case 5 :
        c1=l1.count();
           cout<<"Total no of nodes in a linkedlist are : "<<c1<<endl;
           break;

 case 6 : l1.display();
           break;

case 7 :
        cout<<"Enter the position to delete the node \n";
        cin>>i;
        l1.deletespecific(i);
       l1.display();
           break;
 case 8 :
            cout<<"Enter no. of nodes in 2nd list \n";
            cin>>n;
           for(int i=n-1;i>=0;--i)
            {
            cout<<"Enter the info part of the node "<<i+1<<endl;
             cin>>infos;
              nptr=l2.createnewnode(infos);
               l2.createnewlist(nptr);
             }
           cout<<"Contents of 2nd list are : \n";
           l2.display();
           l3=l1+l2;
            cout<<"contents of concatenate list are : \n";
            l3.display();
             break;

 default: cout<<"Give valid choice \n";
          break;
 }
    }while(choice!=0);

    return 0;
}
