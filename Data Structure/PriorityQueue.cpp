#include<bits/stdc++.h>
using namespace std; 
typedef long long ll;

void printpq(priority_queue <ll> pq) 
{ 
    priority_queue <ll> g = pq; 
    while (!g.empty()) 
    { 
        cout << " " << g.top(); 
        g.pop(); 
    } 
    cout <<"\n"; 
} 
  
int main () 
{ 
    priority_queue <ll> pq; 
    pq.push(10); 
    pq.push(30); 
    pq.push(20); 
    pq.push(5); 
    pq.push(1); 
  
    cout << "The priority queue pq is : "; 
    printpq(pq); 
  
    cout << "\n pq.size() : " << pq.size(); 
    cout << "\n pq.top() : " << pq.top(); 
  
  
    cout << "\n pq.pop() : "; 
    pq.pop(); 
    printpq(pq); 
    
    //OUTPUT:
    //The priority queue pq is: 30 20 10 5 1
    //
    //pq.size() : 5
    //pq.top() : 30
    //pq.pop() : 20 10 5 1
    //
    //By default priority_queue in STL is used to implement max heap. To use priority queue in STL as min heap we need to add extra arguments
    // : priority_queue< data_type, vector<data_type>, compare_type >pq;
    // ex: priority_queue<int, vector<int>, greater<int> >pq;
    
    return 0; 
} 
