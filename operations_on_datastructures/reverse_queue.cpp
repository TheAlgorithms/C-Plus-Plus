#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

queue<int> reverseQueue(queue<int> myQueue) {
    stack<int> myStack;
    int size = myQueue.size();
    for (unsigned int i = 0; i < size; i++) {
        myStack.push(myQueue.front());
        myQueue.pop();
    }
    queue<int> newQueue;
    for (unsigned int j = 0; j < size; j++) {
        newQueue.push(myStack.top());
        myStack.pop();
    }
    return newQueue;
}

int main() {
    queue<int> myQueue;
    string input;
    bool digit = true;

    cout << "To stop the insertion, please enter any non-number" << endl;
    cout << "Enter numbers to insert into the queue: " << endl;

    cin >> input;
    for (unsigned int i = 0; i < input.size(); i++) {
        if (!isdigit(input[i])) {
            digit = false;
        }
    }
    while (digit) {
        myQueue.push(stoi(input));
        cin >> input;
        for (unsigned int i = 0; i < input.size(); i++) {
            if (!isdigit(input[i])) {
                digit = false;
            }
        }
    }

    queue<int> newQueue = reverseQueue(myQueue);
    cout << "Your queue: " << endl;
    int size = myQueue.size();
    for (unsigned int i = 0; i < size; i++) {
        cout << myQueue.front() << " ";
        myQueue.pop();
    }
    cout << endl;
    cout << "Reversed queue: " << endl;
    for (unsigned int j = 0; j < size; j++) {
        cout << newQueue.front() << " ";
        newQueue.pop();
    }
}
