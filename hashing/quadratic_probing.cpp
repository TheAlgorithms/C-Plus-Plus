#include<iostream>
#include<string.h>
using namespace std;

bool isEmpty(int hashTable[], int mod){
    int count = 0; 
    for(int i=0;i<mod;i++){
        if(hashTable[i] == -1)
            count++;
    }
    if(count == mod)
       return true;
    else
       return false;
}

bool isFull(int hashTable[], int mod){
    int count = 0; 
    for(int i=0;i<mod;i++){
        if(hashTable[i] != -1)
            count++;
    }
    if(count == mod)
       return true;
    else
       return false;
}

void display(int hashTable[], int mod){
    if(isEmpty(hashTable, mod)){
       cout<<"Hash Table is empty\n";
       return;
    }
    cout<<"Elements in hash table are:";
    for(int i=0;i<mod;i++){
        if(hashTable[i] != -1){
            cout<<hashTable[i]<<" ";
        }
    }
}

int main(){
    int mod,ele,key,count1 = 0,count2 = 0,p;
    char ch;
    cout<<"Enter the size of hash table:";
    cin>>mod;
    int hashTable[mod];
    memset(hashTable, -1, sizeof(hashTable));
    while(1){
        cout<<"\nSelect the operation\n1.Insertion of element\n2.Deletion of element\n3.Display elements in hash table\n4.Exit\n";
        cout<<"\nEnter your choice:";
        cin>>ch;
        switch(ch){
    
            case '1':  if(isFull(hashTable, mod)){
                            cout<<"\nHash Table is full\n";
                            break;
                       }
                       p = 1;
                       cout<<"Enter element to be inserted:";
                       cin>>ele;
                       key = ele%mod;
                       while(hashTable[key]!=-1){
                            key = (key+(p*p))%mod;
                            count1++; 
                            p++;
                            if(count1 == mod)
                                return 0;
                       }
                       hashTable[key] = ele;
                       break;
         
            case '2':   if(isEmpty(hashTable, mod)){
                            cout<<"\nHash Table is empty\n";
                            break;
                       }
                       p = 1;
                       cout<<"\nEnter element to be deleted:";
                       cin>>ele;
                       key = ele%mod;
                       while(hashTable[key] != ele){
                           key = (key+(p*p))%mod;
                           count2++;
                           p++;
                           if(count2 == mod){
                               cout<<"\nNo such element present!!\n";
                               break;
                           }
                       }
                        cout<<"\nDeleted element is "<<hashTable[key];
                        hashTable[key] = -1;
                       break;
 
            case '3':  display(hashTable, mod);
                       break;

            case '4':    exit(0);

            default:   cout<<"\nInvalid choice!\n";
        }
    }
    return 0;
}

