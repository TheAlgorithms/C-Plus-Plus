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
  
    return 0; 
} 
