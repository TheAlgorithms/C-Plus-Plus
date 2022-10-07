
#include <bits/stdc++.h>

using namespace std;

// creating node structure  which  will be  used in  hashing with seperate chaining.

class Node{
    public:
    long long data ;
    Node* next = 0;
Node(int data){
    this->data=data;
    next=0;
};
};
class HashTable_by_chaining{
    public:
    Node* HT[11]={0}; // here i have taken array of type Node* of  size 11 i.e it can store 11 pointer you can take it according to you
    int Hash_function(int data)
  //This is my Hash function
    {
    return  data %10;
      }
  
    void insert(int data)
//       This is my insert function
    {
        int hashkey=Hash_function(data);
        if (HT[hashkey]==0){
            Node *t=new Node(data);
            HT[hashkey]=t;

        }
        else{
            Node * t=HT[hashkey];
            Node *r =0 ;
            while (t!=0){
                r=t;
                t=t->next;
            }
            Node *entry=new Node(data);
            r->next=entry;
        }
        }
//   this is my search function
    bool search(int data){
        int hashkey=Hash_function(data);
            Node* t=HT[hashkey];
            cout<<"["<<hashkey<<"] ";
            while(t->data!=data){
                // cout<<t->data<<" ";
                t=t->next;
                if (t==0){
                   
                     return 0;
                    
                }
            }if (t==0){
                return 0;
            }
            else{
            return 1;
            }
        }
  
//   this is delete function
    void delete_entry(int data){
         int hashkey=Hash_function(data);
            Node* t=HT[hashkey];
            Node *r=0;
        if (search(data)){
                while(t->data!=data){
                r=t;
                t=t->next;
            }
            if (HT[hashkey]==t){
            
            if (t->next!=0){
              t=t->next;
              HT[hashkey]=t;
            }
            else{
                HT[hashkey]=0;
            }
            
            }
            else{
                r->next=t->next;
            }
            
    }};
  
//   this is the print function
    void printHT()
    {
   cout<<"HashTable"<<endl;
        for(int i=1 ;i<11;i++){

            cout<<"["<<i<<"] ";
            Node* t=HT[i];
            while (t!=0){
                cout<<t->data<<"->";
                t=t->next;

            }
            cout<<"NULL"<<endl; 
        }
    }
    };
int hashingFunction(int data){
    return data%10;
}
// #####################################################################################################################################################################

// this is hashing by  linear proabing
class HashTable_by_linear_proabing{
    public:
    int Table_size=10;
     int HT[10]={0};

     int Hashing(int data){
         return data%10;
     }

void insert(int data)
//  this is insert function
{
    int Hashkey=Hashing(data);
    if(HT[Hashkey]==0){
//       if hashed index is empty then place the element there
        HT[Hashkey]=data;
    }
    else {
      else travserse till next we find a empty location
            while (HT[Hashkey]!=0)
            {
                Hashkey ++;
            }
            HT[Hashkey]=data;
    }


}
void display(){
    for(int i=0;i<10;i++){
        cout<<i<<" - "<<HT[i]<<endl;
    }
}
};

int main ()
{
    HashTable_by_chaining h;  // object is created of HashTable_by_chaining 
    h.insert(11);
    h.insert(11);
    h.insert(12);
    h.insert(73);
    h.insert(193);
    h.insert(963);
    h.insert(114);
    h.insert(2456);
    h.insert(5698);
    h.search(5666);
    h.printHT();
    cout<<endl;
    h.delete_entry(193);
    h.delete_entry(2456);
    h.printHT();
  
  
  
HashTable_by_linear_proabing hl;  // object id created of HashTable_by_linear_proabing
  
hl.insert(1);
hl.insert(61);
hl.insert(21);
hl.insert(31);
hl.insert(51);
hl.display();
return 0;
}
