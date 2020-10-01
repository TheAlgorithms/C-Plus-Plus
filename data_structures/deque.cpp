#include <iostream> 
#include <deque> 
  
using namespace std; 
  
void showdq(deque <int> g) 
{ 
    deque <int> :: iterator it; 
    for (it = g.begin(); it != g.end(); ++it) 
        cout << '\t' << *it; 
    cout << '\n'; 
} 
  
int main() 
{ 
    deque <int> gquiz; 
    gquiz.push_back(10); 
    gquiz.push_front(20); 
    gquiz.push_back(30); 
    gquiz.push_front(15); 
    cout << "The deque gquiz is : "; 
    showdq(gquiz); 
  
    cout << "\ngquiz.size() : " << gquiz.size(); 
    cout << "\ngquiz.max_size() : " << gquiz.max_size(); 
  
    cout << "\ngquiz.at(2) : " << gquiz.at(2); 
    cout << "\ngquiz.front() : " << gquiz.front(); 
    cout << "\ngquiz.back() : " << gquiz.back(); 
  
    cout << "\ngquiz.pop_front() : "; 
    gquiz.pop_front(); 
    showdq(gquiz); 
  
    cout << "\ngquiz.pop_back() : "; 
    gquiz.pop_back(); 
    showdq(gquiz); 
  
    return 0; 
} 
