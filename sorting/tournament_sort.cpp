//tournament sort
// Not an in place sorting
// An additional binary tree is used to the store the values
//where each parent node will have the maximum of its two children
//All n values of the list are stored in the leaves of the tree

#include <iostream>
#include <limits.h>


//inserts the element in to the tree


void trinsert(int A[],int *num,int val){
    //num is the number of nodes in the tree
int n=*num;
// if num is 0, first elements
    if(!n){
        A[n++]=val;
        return;
    }
//below code finds the finds the first leaf and makes it a parent with
//two children - one the value of the parent itself and the other the new value
    int p=(n-1)/2;
    A[2*p+1]=A[p];
    A[2*p+2]=val;


    int i=n;
    i=(i-1)/2;
    while(i>=0){
        if(A[2*i+1]>A[2*i+2]){
            A[i]=A[2*i+1];
        }
        else{
            A[i]=A[2*i+2];
        }
        if(!i){
            break;
        }
        i=(i-1)/2;
    }
    n+=2;
   *num=n;
}
// Extracts the root element and returns it
int maxdelete(int A[],int *n){
    int i,pivot;
    i=0;
// pivot is the max element of the list
    pivot=A[i];
//
    while(i<=(*n-2)/2){
        if(A[2*i+1]==pivot){
            i=2*i+1;
        }
        else{
            i=2*i+2;
        }
    }

    
    A[i]=A[*n-1];
    A[*n-1]=INT_MIN;
    i=(i-1)/2;
    while(i>=0){
        if(A[2*i+1]>A[2*i+2]){
            A[i]=A[2*i+1];
        }
        else{
            A[i]=A[2*i+2];
        }
        if(i==0){
            break;
        }
        i=(i-1)/2;
    }


    i=(*n-2)/2;
    while(i>=0){
        if(A[2*i+1]>A[2*i+2]){
            A[i]=A[2*i+1];
        }
        else{
            A[i]=A[2*i+2];
        }
        if(i==0){
            break;
        }
        i=(i-1)/2;
    }


    if(*n==1){
        *n=0;
    }
    else{
        *n-=2;
    }
   return pivot; 
}
void tournament_sort(int A[],int n){
//let B be the binary tree 
    int B[2*n-1];
    int num=0;
    for(int i=0;i<n;i++){
        trinsert(B,&num,A[i]);
    }
    for(int i=0;i<n;i++){
        A[n-i-1]=maxdelete(B,&num);
    }
}
int main(){
    int n;
    std::cin>>n;
    int A[n];
    for(int i=0;i<n;i++){
        std::cin>>A[i];
    }
    tournament_sort(A,n);
    for(int i=0;i<n;i++){
        std::cout<<A[i]<<" ";
    }
    std::cout<<std::endl;
    return 0;
}
