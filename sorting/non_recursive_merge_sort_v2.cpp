#include <iostream>
/**
 * @file non_recursive_merge_sort_v2.cpp
 * @brief A non recursive top down implementation of merge sort
 * @details 
 * Sorts input array in non decreasing order
 * Uses tree like post order traversal
 * Template Stack and custom range pair datastructure defined
 * @author [Shiven Tripathi](https://github.com/ShivenTripathi)
 * 
 */
namespace sorting{
template <class T>
class Stack{
    public:
    int top; //this contains the index of the last element to enter the Stack
    T *A; //our stack is implemented over an array
    int maxsize;
    
        Stack(int size);
        int isEmpty();
        int isFull();
        int Push(T x);
        T Pop();
        T Top();        
};
template <class T>
Stack<T> ::Stack(int size){
//constructor to initialise top to -1, denoting empty stack
    A = new T[size];
    top = -1;
    maxsize = size;
}
template <class T>
int Stack<T>::isEmpty(){
//when stack is empty, top = -1, with which it had been initialised
    if( top == -1)
        return 1;
    else 
        return 0;
}
template <class T>
int Stack<T>::isFull(){
//maximum inex we can have in array is maxsize-1 and we return 1 for isFull when top is the maximum index and we can't insert any further
    if( top == maxsize-1 )
        return 1;
    else
        return 0;
}
template <class T>
int Stack<T>::Push(T x){
    //check for overflow
    if( isFull() == 1 )
        return 1;
    else{
        //increment top to next available index and set A[top] to the element to be inserted
        top++;
        A[top] = x;
        return 0;
    }
}
template <class T>
T Stack<T>::Pop(){
    //check for underflow
    if( isEmpty() == 1)
        return {-1}; //TODO: better exception handling according to specifications
    else{
        //decrement top to previous index, thus removing access to the last element to enter
        T temp = A[top];
        top--;
        return temp;
    }
}
template <class T>
T Stack<T>::Top(){
     if( isEmpty() == 1)
        return {-1}; //TODO: better exception handling according to specifications
    else{
        return A[top];
    }
}
void merge(int A[],int B[],int start, int middle, int end){
    //initialise our iterators, i for the first half, j for the second half, k for the merged aux array B
    long i=start,j=middle+1,k=start;
    //iterating till we have used all the elements for filling aux array B
    while(k<=end){
        //this block executed when we have unseen elements in left and right half and the iterator pointing to left half is smaller
        if(i<=middle && j<=end && A[i]<=A[j]){
            B[k]=A[i];
            k++; //increment k since we filled in another element
            i++; //increment i since we used up another element from left half
            continue;
        }
        //this block executed when we have unseen elements in left and right half and the iterator pointing to right half is smaller
        if((i<=middle && j<=end && A[i]>A[j])){
            B[k]=A[j];
            k++; //increment k since we filled in another element
            j++; //increment j since we used up another element from right half
            continue;
        }            
        if(i<=middle && j>end){
            B[k]=A[i];
            k++; //increment k since we filled in another element
            i++; //increment i since we used up another element from left half
            continue;
        }            
        if(i>middle && j<=end){
            B[k]=A[j];
            k++; //increment k since we filled in another element
            j++; //increment j since we used up another element from right half
            continue;
        }
    }
    //copying over our merged in order aux to A
    for(k=start;k<=end;k++){
        A[k]=B[k];
    }    
}

//We define a custom pair data structure which would make up our stack
class pairLR{
    public:
    int start; //this is the starting index of our array half
    int end; //this is the last index of our array half
    int isNull(){
        // this function tells us whether our range is valid or not, consider it to be telling us whether size of our array half is more than 1 or not
        if(start<end)
            return 0;
        else 
            return 1;
    }
};
//utility functions defined from here
pairLR makePair(int low, int up){
    //use this to initalise/make when you really dont want to use a constructor
        pairLR temp;
        temp.start=low;
        temp.end=up;
        return temp;
}
pairLR leftChild(pairLR x){
    //visualise as when we recur on left subhalf of array
        return makePair(x.start,(x.start+x.end)/2);
}
pairLR rightChild(pairLR x){
    //visualise as when we recur on left subhalf of array
        return makePair((x.start+x.end)/2+1, x.end);
}
int equal_To(pairLR x, pairLR y){
    //checks for equality between array halves
    if(x.start==y.start && x.end==y.end)
        return 1;
    else
        return 0;
}
void prt(pairLR x){
    //utility to print    
    std::cout<<x.start<<" "<<x.end<<"\n";
}
void mergeSort(int A[], int start, int end){
    //creating auxiliary array
    int B[end+1];
    //creating our stack to store array first and last indices
    Stack <pairLR> S(50);
    
    //curr is the node we are on right now, (obviously!), we initialise it with entire array
    pairLR curr=makePair(start,end);
    pairLR last=makePair(-1,-1); //initialise to invalid
    pairLR peek=makePair(-1,-1); //iniialise to invalid
    
    //we use postorder traversal, to simulate function call stacks 
    while(!S.isEmpty() || !curr.isNull()){
        
        //this block lets us push to smaller left halves, something similar to what happens in recursion
        if( !curr.isNull() ){
            S.Push(curr);
            curr=leftChild(curr);
        }
        
        //our curr is not valid anymore
        else{
            peek=S.Top();
            //check if the righchild (right sub array) is valid and has not been visited in the previous iteration
            //since we move towards right children only in this block, safe to just check with last
            if( !rightChild(peek).isNull() && !equal_To(rightChild(peek),last)){
                curr=rightChild(peek); //rightchild(peek) is valid and not visited, therefore we can push it
            }
            else{
                //in case the right child is not valid or has been visited alread (read: merged), we can take it to involve 2 sorted subarrays and merge them
                merge(A,B,peek.start,(peek.start+peek.end)/2,peek.end);
                last=S.Pop(); //last maintains the previous merged array
            }
        }
    }
}
}
/*
Example:
INPUT: 
2
10
383 886 777 915 793 335 386 492 649 421
10
362 27 690 59 763 926 540 426 172 736
OUTPUT:
335 383 386 421 492 649 777 793 886 915 
27 59 172 362 426 540 690 736 763 926 
*/
int main() {
    int t,i; //t is the number of test cases, i our loop iterator
    std::cin>>t;
    while(t--){
        int N; //N is the number of elements in array A
        std::cin>>N;
        int A[N];
        
        //inserting each element into array
        for(i=0;i<N;i++){
            std::cin>>A[i];
        }
        
        //calling our mergesort procedure
        sorting::mergeSort(A,0,N-1);
        
        //getting output 
        for(i=0;i<N;i++){
            std::cout<<A[i]<<" ";
        }std::cout<<"\n";
    }
    return 0;
}
