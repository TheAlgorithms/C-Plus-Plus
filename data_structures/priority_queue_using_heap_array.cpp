#include <iostream>
#define MAX_ELEMENTS 1000
class Priority_queue{
// A is the array implementation of the heap which stores the values
// n is the number of elements currently present in the heap
    int A[MAX_ELEMENTS];
    int n;

    public:
        Priority_queue();
        void display();
        int max();
        void insert(int );
        void max_heapify(int );
        int getmax();

};

//initializes n as 0
Priority_queue::Priority_queue(){
    n=0;
}

//inserts  a new value 'val' at the next possible leaf and swaps its value with the parent iteratively till parent[i] is smaller to find it's correct position
void Priority_queue::insert(int val){
    A[n++]=val;
    int i,temp;
    i=n-1;
    while(i>0 && A[(i-1)/2]<A[i]){
        temp=A[i];
    // if parent is smaller, swap and then point i at the position of parent
        A[i]=A[(i-1)/2];
        A[(i-1)/2]=temp;
    }
}
// displays the priority queue as it is present in the heap (it won't be sorted since childs may not be in the sorted order but you can visualize the tree)
void Priority_queue::display(){
    for(int i=0;i<n;i++){
        std::cout<<A[i]<<" ";
    }
    std::cout<<std::endl;
}
// returns maximum value(that is present at the root)
int Priority_queue::max(){
    return A[0];

}
// max heapifies(or makes a max_heap) from the ith node onwards
void Priority_queue::max_heapify(int i){
    int temp,largest,l,r;
    l=2*i+1;
    r=2*i+2;
    if(l<n && A[l]>A[i]){
        largest=l;
    }
    else{
        largest=i;
    }
    if(r<n && A[r]>A[largest]){
        largest=r;
    }
    if(largest!=i){
        temp=A[i];
        A[i]=A[largest];
        A[largest]=temp;
        max_heapify(largest);
    }
}
// extracts and return the maximum element(which is at the root)
int Priority_queue::getmax(){
    int max=A[0];
    A[0]=A[--n];
    max_heapify(0);
    return max;
}
int main(){
    Priority_queue A;
    char c='0';
    int val;
    std::cout<<"i : (followed by an integer) to insert a new value to the priority queue\n";
    std::cout<<"d : to display the priority queue\n";
    std::cout<<"m : to display the maximum element of the queue\n";
    std::cout<<"r : to extract and print the maximum element of the queue\n";
    std::cout<<"s : to exit the program\n";
    while(c!= 's'){
        std::cin>>c;
        switch(c){
            case 'i':std::cin>>val;
                     A.insert(val);
                     break;
            case 'd':A.display();
                    break;
            case 'm':val=A.max();
                     std::cout<<val<<std::endl;
                     break;
            case 'r':val=A.getmax();
                     std::cout<<val<<std::endl;
                    break;
            case 's':break;
            default: std::cout<<"Invalid input "<<std::endl;
                    
        }
    }
}