#include<iostream>
using namespace std;
struct Node{
    int data;
    int priority;
    Node* next;
};
class PQ{
    private:
        Node* front;
    public:
        PQ(){
            front=NULL;
        }
    void insert(int,int);
    void remove();
    bool isEmpty();
    void display();
};
void PQ::insert(int value,int p){
    Node* newNode=new Node;
    newNode->data=value;
    newNode->priority=p;
    if(front==NULL||p<front->priority){
        newNode->next=front;
        front=newNode;
    }
    else{
        Node* curr=front;
        while(curr->next&&curr->next->priority<=p){
            curr=curr->next;
        }
        newNode->next=curr->next;
        curr->next=newNode;
    }
}
void PQ::remove(){
    while(!isEmpty()){
        Node* temp=front;
        front=front->next;
        delete temp;
    }
}
bool PQ::isEmpty(){
    return front==NULL;
}
void PQ::display(){
    if(isEmpty()){
        cout<<"Priority Queue is empty"<<endl;
        return;
    }
    Node* temp=front;
    while(temp!=NULL){
        cout<<"Value: "<<temp->data<<endl;
        cout<<"Priority: "<<temp->priority<<endl;
        temp=temp->next;
    }
}
int main(){
    PQ p;
    int ch;
    cout<<"1.Insert"<<endl;
    cout<<"2.Remove"<<endl;
    cout<<"3.Display"<<endl;
    cout<<"4.Exit"<<endl;
    do{
        cout<<"Enter your choice"<<endl;
        cin>>ch;
        switch(ch){
            case 1:cout<<"Enter the value to be inserted"<<endl;
                   int value,priority;
                   cin>>value;
                   cout<<"Enter the priority"<<endl;
                   cin>>priority;
                   p.insert(value,priority);
                   break;
            case 2:p.remove();
                   break;
            case 3:p.display();
                   break;
            case 4:exit(1);
                   break;
            default:cout<<"Invalid Choice"<<endl;
        }
    }while (ch!=5);
    return 0;   
}