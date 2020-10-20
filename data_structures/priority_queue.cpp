// Note that by default C++ creates a max-heap 
// for priority queue


 
#include <iostream> 
#include <queue> 

using namespace std; 

void showpq(priority_queue <int> gq) 
{ 
	priority_queue <int> g = gq; 
	while (!g.empty()) 
	{ 
		cout << '\t' << g.top(); 
		g.pop(); 
	} 
	cout << '\n'; 
} 

int main () 
{ 
	priority_queue <int> gquiz; 
	gquiz.push(10); 
	gquiz.push(30); 
	gquiz.push(20); 
	gquiz.push(5); 
	gquiz.push(1); 

	cout << "The priority queue gquiz is : "; 
	showpq(gquiz); 

	cout << "\ngquiz.size() : " << gquiz.size(); 
	cout << "\ngquiz.top() : " << gquiz.top(); 


	cout << "\ngquiz.pop() : "; 
	gquiz.pop(); 
	showpq(gquiz); 

	return 0; 
} 
