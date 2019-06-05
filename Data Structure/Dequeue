#include <iostream>
using namespace std;

const int MAX = 1e5;

class Deque
{
private:
	int data[MAX];
	int index_front;
	int index_back;
public:
	Deque();
	bool empty();
	void push_front(int x);
	void push_back(int x);
	void pop_front();
	void pop_back();
	int front();
	int back();
	int size();
};

Deque::Deque() {
	index_front = 0;
	index_back = 0;
}

bool Deque::empty() {
	return index_front == index_back;
}

void Deque::push_front(int x) {
	data[index_front] = x;
	index_front = (index_front - 1 + MAX) % MAX;
}

void Deque::push_back(int x) {
	index_back = (index_back + 1) % MAX;
	data[index_back] = x;
}

void Deque::pop_front() {
	index_front = (index_front + 1) % MAX;
}

void Deque::pop_back() {
	index_back = (index_back - 1 + MAX) % MAX;
}

int Deque::front() {
	return data[(index_front + 1) % MAX];
}

int Deque::back() {
	return data[index_back];
}

int Deque::size() {
	return (index_back - index_front + MAX) % MAX;
}

int main() {
	Deque dq;
	for (int i = 1; i <= 3; i++) dq.push_front(i);  // Push front 1~3
	dq.pop_front();     // Pop front
	for (int i = 4; i <= 6; i++) dq.push_back(i);   // Push back 4~6
	dq.pop_back();      // Pop back
	dq.push_front(7);   // Push front 7
	Deque dq2 = dq;     // Copy deque
	cout << "* Pop Back: ";
	while (!dq.empty()) {
		cout << dq.back() << " -> ";
		dq.pop_back();  // Pop back all
	}
	cout << "\n* Pop Front: ";
	while (!dq2.empty()) {
		cout << dq2.front() << " -> ";
		dq2.pop_front();  // Pop front all
	}
	return 0;
}

//reference: https://rebas.kr/797 [PROJECT REBAS]
//the result should be
//Size: 5
//Pop Back: 5->4->1->2->7->
//Pop Front: 7->2->1->4->5->
//MAX : max size of dequeue. it can reschedule the max size when change the value.
//Data: the array of elements dequeue.
//index_front: the value of front element
//index_back: the value of back element
