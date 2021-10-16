/* 
We are given a Queue data structure that supports standard operations like enqueue() and dequeue(). 
We need to implement a Stack data structure using only instances of Queue and queue operations allowed on the instances.

Program to implement a stack using two queue 

A stack can be implemented using two queues. Let stack to be implemented be ‘s’ and queues used to implement be ‘q1’ and ‘q2’. 

This method makes sure that newly entered element is always at the front of ‘q1’, so that pop operation just dequeues from ‘q1’. 
‘q2’ is used to put every new element at front of ‘q1’.
 
push(s, x) operation’s step are described below: 
Enqueue x to q2
One by one dequeue everything from q1 and enqueue to q2.
Swap the names of q1 and q2
pop(s) operation’s function are described below: 
Dequeue an item from q1 and return it.
Below is the implementation of the above approach: 


*/
/* Program to implement a stack using
two queue */
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>


class Stack {
	// Two inbuilt queues
	std::queue<int> q1, q2;

	// To maintain current number of
	// elements
	int curr_size;

public:
	Stack()
	{
		curr_size = 0;
	}

	void push(int x)
	{
		curr_size++;

		// Push x first in empty q2
		q2.push(x);

		// Push all the remaining
		// elements in q1 to q2.
		while (!q1.empty()) {
			q2.push(q1.front());
			q1.pop();
		}

		// swap the names of two queues
		std::queue<int> q = q1;
		q1 = q2;
		q2 = q;
	}

	void pop()
	{

		// if no elements are there in q1
		if (q1.empty())
			return;
		q1.pop();
		curr_size--;
	}

	int top()
	{
		if (q1.empty())
			return -1;
		return q1.front();
	}

	int size()
	{
		return curr_size;
	}
};

// Driver code
int main()
{
	Stack s;
	s.push(1);
	s.push(2);
	s.push(3);

	std::cout << "current size: " << s.size() << std::endl;
	std::cout << s.top() << std::endl;
	s.pop();
	std::cout << s.top() << std::endl;
	s.pop();
	std::cout << s.top() << std::endl;

	std::cout << "current size: " << s.size() << std::endl;
	return 0;
}
