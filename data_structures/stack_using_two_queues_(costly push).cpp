#include<iostream>

#include<queue>

using namespace std;

void pop(queue < int > & q1) {
  cout << q1.front() << " has been popped\n";
  q1.pop();
}

void push(queue < int > & q1, queue < int > & q2, int num) {
  q2.push(num);
  while (!q1.empty()) {
    q2.push(q1.front());
    q1.pop();
  }
  swap(q1, q2);
}

void display(queue < int > q1, queue < int > q2) {
  int n = q1.size();
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      q2.push(q1.front());
      q1.pop();
    }
    cout << q1.front() << " ";
    q1.pop();
    swap(q1, q2);
  }
  cout << "\n";
}

int main() {
  queue < int > q1, q2;
  push(q1, q2, 1);
  push(q1, q2, 2);
  push(q1, q2, 3);
  push(q1, q2, 4);
  display(q1, q2);
  pop(q1);
  display(q1, q2);
  pop(q1);
  display(q1, q2);
  return 0;
}
