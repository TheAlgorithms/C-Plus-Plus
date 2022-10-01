#include <iostream>

using namespace std;
template <class T>
class cnode
{
public:
     T info;
     cnode *next;
     cnode(T x, cnode *n=NULL)
     {
         info=x;
         next=n;
     }
};
template <class T>
class cllist
{
    cnode<T> *cursor;
public:
    cllist()
    {

        cursor=NULL;
    }
    void input();
    int isempty()
    {

        if(cursor==0)
            return 1;
        else
            return 0;
    }
    void addtofront(T x);
    void addtoback(T x);
    void addafter(T x, T y);
    T deletefromfront();
    T deletefromback();
    void deletenode(T x);
    cnode<T> *isinlist(T x);
    cllist<T> operator+(cllist<T> l1);
    void display();

};

template <class T>
void cllist<T>::input()
{
    int n;
    T x;
    cout<<"Enter the number of nodes in cllist :"<<endl;
    cin>>n;
    for(int i=0; i<n; i++)
    {

        cout<<"Enter info part:"<<i+1<<":"<<endl;
        cin>>x;
        addtoback(x);
    }
}
template<class T>
void cllist<T>:: addtofront(T x)
{

    cnode<T> *temp=new cnode<T>(x);
    if(isempty())
    {

        cursor=temp;
        temp->next=cursor;
    }
    else
    {

        temp->next=cursor->next;
        cursor->next=temp;
    }
}
template<class T>
void cllist<T>::addtoback(T x)
{
    cnode<T> *temp=new cnode<T> (x);
    if(isempty())
    {
        cursor=temp;
        cursor->next=temp;
        cursor=temp;
    }
    else
    {

        temp->next=cursor->next;
        cursor->next=temp;
        cursor=temp;
    }
}
template <class T>
void cllist<T>::addafter(T x,T y)
{
    cnode<T> *nptr=new cnode<T>(x);
    cnode<T> *temp;
    temp=cursor->next;
    do{
        if(temp->info==y)
        {
            if(temp==cursor)
            {
                addtoback(x);
            }
            else{
                nptr->next=temp->next;
                temp->next=nptr;
            }
        }
        temp=temp->next;
    }while(temp!=cursor->next);
}
template<class T>
T cllist<T>::deletefromfront()
{
    cnode<T> *temp;
    T x;
    x=cursor->next->info;
    if(cursor->next==cursor)
    {
        delete cursor;
        cursor=NULL;
    }
    else
    {
        temp=cursor->next;
        cursor->next=temp->next;
        delete temp;
    }
    return x;
}
template <class T>
T cllist<T>::deletefromback()
{
    cnode<T>*temp;
    T x=cursor->info;
    if(cursor->next==cursor)
    {
        delete cursor;
        cursor=NULL;
    }
    else
    {

        temp=cursor->next;
        while(temp->next!=cursor)
        {
            temp=temp->next;
        }
        temp->next=cursor->next;
        delete cursor;
        cursor=temp;
    }
    return x;
}
template <class T>
void cllist<T>::deletenode(T x )
{
cnode<T> *prev;
cnode<T>*current;
if(cursor->next==cursor&&cursor->info==x)
{
    delete cursor;
    cursor=NULL;
}
else if(cursor->next->info==x)
{
    current=cursor->next;
    cursor->next=current->next;
    delete current;
}
else{
    prev=cursor->next;
    current=prev->next;
    while(current!=cursor&&current->info!=x)
    {

        prev=current;
        current=current->next;
    }
    if(current!=cursor->next)
    {
        prev->next=current->next;
        if(current==cursor)
        {
            cursor=prev;
        }
        delete current;
    }
    else{
        cout<<"Element not found"<<endl;
    }
}
}
template<class T>
cnode<T>*cllist<T>::isinlist(T x)
{
    cnode<T>*temp;
    temp=cursor->next;
    do{
        if(temp->info==x)
        {
            return temp;
        }
        temp=temp->next;
    }
    while(temp!=cursor->next);
    return NULL;
}
template<class T>
cllist<T>cllist<T>::operator+(cllist<T>l1)
{
    cllist<T>l3;
    cnode<T> *temp;
    if(!(*this).isempty());
    {
        temp=(*this).cursor->next;
        do{
            l3.addtoback(temp->info);
            temp=temp->next;
        }
        while(temp!=(*this).cursor->next);
    }
    if(!l1.isempty())
    {
        temp=l1.cursor->next;
        do{
            l3.addtoback(temp->info);
            temp=temp->next;
        }while(temp!=l1.cursor->next);
    }
    return l3;
}
template <class T>
void cllist<T>::display()
{
    cnode<T> *temp;
    temp=cursor->next;
    do{
        cout<<temp->info<<"\t";
        temp=temp->next;
    }
    while(temp!=cursor->next);
}
int main()
{
   cllist<int>l1,l2,l3;
   char ch='y';
   int choice,x,a,d,n;
   cnode<int>*temp;
   l1.input();
   while(ch=='y'||ch=='y')
   {
       cout<<"***MAIN MENU***"<<endl;
       cout<<"1. ADD TO FRONT OF CLLIST :"<<endl;
       cout<<"2. ADD TO BACK OF CLLIST :"<<endl;
       cout<<"3. ADD TO AFTER Y OF CLLIST :"<<endl;
       cout<<"4. TO DELETE ELEMENT FROM FRONT: "<<endl;
       cout<<"5. TO DELETE ELEMENT FROM BACK :"<<endl;
       cout<<"6. TO DELETE THE NODE FROM CLLIST :"<<endl;
       cout<<"7. TO SEARCH THE ELEMENT OF CLLIST:"<<endl;
       cout<<"8. TO CONCATENATE ELEMENT OF THE CLLIST:"<<endl;
       cout<<"9. TO DISPLAY THE CIRCULAR LINKED LIST :"<<endl;
       cout<<"ENTER YOUR CHOICE :";
       cin>>choice;
       switch(choice)
       {
           case 1: cout<<"Enter the info part of the node to be added"<<endl;
                   cin>>x;
                  // x=l1.input();
                   l1.addtofront(x);
                   l1.display();
                   break;

           case 2:  cout<<"Enter the info part of the node to be added"<<endl;
                   cin>>x;
                   //x=l1.input();
                   l1.addtoback(x);
                   cout<<"The element of cllist are"<<endl;
                    l1.display();
                   break;
          case 3: if((!l1.isempty()))
                 {
                     cout<<"Enter the info part of the node after which you want to add :"<<endl;
                     cin>>a;
                     cout<<"Enter the info part of new node:"<<endl;
                     cin>>x;
                     l1.addafter(x,a);
                  l1.display();
                 }
                 else
                 {
                     cout<<"The cllist is Empty! "<<endl;
                 }
                 break;
           case 4: if(!(l1.isempty()))
                 {
                  d=l1.deletefromfront();
                  cout<<"Deleted element is:"<<d<<endl;
                  l1.display();
                 }
                 else
                 {
                     cout<<"The cllist is Empty! "<<endl;
                 }
                 break;
          case 5:if(!(l1.isempty()))
                 {
                     d=l1.deletefromback();
                    cout<<"Deleted element is:"<<d<<endl;
                    cout<<"your cllist is:"<<endl;
                  l1.display();
                 }
                 else
                 {
                     cout<<"The cllist is Empty! "<<endl;
                 }
                 break;
        case 6:if((!l1.isempty()))
                 {
                     cout<<"Enter the value which you want to delete :"<<endl;
                     cin>>a;
                     l1.deletenode(a);
                  l1.display();
                 }
                 else
                 {
                     cout<<"The cllist is Empty! "<<endl;
                 }
                 break;
        case 7:if(l1.isempty())
                {
                 cout<<"List is empty !!"<<endl;
                }
                else
                 {
                     cout<<"Enter the value which you want to search :"<<endl;
                     cin>>x;
                     temp=l1.isinlist(x);
                     if(temp==NULL)
                        {
                        cout<<"We have  not found the element in cllist:"<<endl;
                 }
                        else{
                            cout<<" We have found the element in cllist:"<<endl;
                        }
                 }
                 break;
        case 8:l2.input();
               cout<<"Your 2nd cllist is"<<endl;
                l2.display();
                l3=l1+l2;
                cout<<"Your concatenated list is"<<endl;
                l3.display();
                  break;
        case 9: cout<<"Element of Cllist are:"<<endl;
                l1.display();
                break;

        default: cout<<"ERROR IN INPUT !!!"<<endl;
       }
       cout<<endl;
       cout<<"DO YOU WANT TO CONTINUE(Y/N):";
       cin>>ch;

   }
    return 0;
}
