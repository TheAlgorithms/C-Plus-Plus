// Span Problem 
// Here we have to find span of every element in an array, i.e number of consecutive elements before that element (including that element also)
// having values less than or equal to value of current element
// Note: Span of every element will be at least 1 


#include<iostream>
#include<stack>
using namespace std;

// function for span problem

// We have made use std::stack but you can also define your own stack using structure or classes
void spans(int *a, int n, int *span){
    stack<int> s;  
    
    for(int i = 0; i<n; i++){
        while(!s.empty() && a[i]>=a[s.top()]){
            s.pop();
        }
        if(s.empty()){
            span[i] = i+1;
            s.push(i);
        }
        else{
            span[i] = i-s.top();
            s.push(i);
        }
   }
   
}

//testing our span function
int main(){
    //test-1
    cout<<"TEST-1\n";
    int a[] = {9,12,5,13};
    int span_a[4];
    stack<int> s;
    spans(a,4,span_a);
    for(int i = 0 ; i<4; i++)
        cout<<span_a[i]<<" ";

    //test-2
    cout<<"\nTEST-2\n";
    int b[] = {1,32,5,76,56};
    int span_b[5];
    stack<int> ss;
    spans(b,5,span_b);
    for(int i = 0 ; i<5; i++)
        cout<<span_b[i]<<" ";
    
}
