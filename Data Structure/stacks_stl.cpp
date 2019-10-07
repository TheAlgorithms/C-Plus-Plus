
#include <iostream> 
#include <stack> 
using namespace std; 
  
void showstack(stack <int> s) 
{ 
    while (!s.empty()) 
    { 
        cout << '\t' << s.top(); 
        s.pop(); 
    } 
    cout << '\n'; 
} 
  
int main () 
{ 
    stack <int> s; 
    int n;
    cin>>n;//number of element user want to insert in stack
    for(int i=0;i<n;i++){
      int data;
      cin>>data;
      s.push(data);
    }
  
    cout << "The stack is : "; 
    showstack(s); 
  
    cout << "\ns.size() : " << s.size(); 
    cout << "\ns.top() : " << s.top(); 
  
  
    cout << "\ns.pop() : "; 
    s.pop(); 
    showstack(s); 
  
    return 0; 
} 
