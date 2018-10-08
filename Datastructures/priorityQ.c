/*
1.priority queue is a type of queue in which elements are inserted in the order of their priori
2.In the following program it is being implemented using linked lists in c.
3.Apart from data and the address of the next node , a node also contains the priority. 
4. it has been assumed that lower the value of priority value , the earlier it will be removed from the queue.
5. It is practically very important in case of client server realtion in which some users have some special grants.


*/


#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    int priority;
    struct node* next;
};
typedef struct node node;
node* front=NULL;
node* rear=NULL;
node* head=NULL;

//The following function will return address of the node created, which can be used in the linked lists
node* getnode()
{
    return (node*)malloc(sizeof(node));
}

void insertionInQ(int data,int p) {
    node * neww = getnode();
    neww-> data = data;
    neww-> next = NULL;
    neww->priority=p;
    if (front == NULL && rear == NULL) {
        head = neww;
        front = head;
        rear = head;
    } else {
        rear->next = neww;
        rear = rear->next;
    }
    
}

//below function will be called tofree the memory being allocated to the node to be freed
void freenode(node* p)
{
    free(p);
}

//below code will return the location at which the nide is to be inserted. i.e we have to find the location according to the priority.
node* findloc(int p)
{
    node* loc=NULL;
    node* save=head;
    node* ptr=save->next;
    while(ptr!=NULL)
    {
        if(p<=head->priority||head==NULL)
            loc=NULL;
        if(p<=ptr->priority)
        {
            loc=save;
            return loc;
        }
        else{
            save=ptr;
            ptr=ptr->next;
        }
        
        
    }
    loc=ptr;
    return loc;
}

void displayQ() {
    node * temp = head;
    while (temp != NULL) {
        printf("|%d|%d| -> ", temp->data,temp->priority);
        temp = temp->next;
    }
    printf("NULL\n");
}


void insertionInQP(int data,int p) {
    node* loc=findloc(p);
    node * neww = getnode();
    neww->data = data;
    neww->priority=p;
    if(loc==NULL)
    {
        
        head = neww;
        front = head;
        rear = head;
        neww->next = NULL;
        
    }
    else{
        
        neww->next=loc->next;
        loc->next=neww;
        
        
    }
    
    
}

int main()
{   

	/* 
	the following four function call is to insert the nodes accoring to the priorites. 5th function call is different in  the way that
	it will have some random priority ranking and it needs to be inserted in the queue acc to its deserving place 

	*/
    insertionInQ(10,1);
    insertionInQ(11, 2);
    insertionInQ(34, 5);
    insertionInQ(56, 8);   
    insertionInQP(45, 4);
    displayQ();
    
    return 0;
}
