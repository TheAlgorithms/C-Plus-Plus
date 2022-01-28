/**
 * @file
 * @brief Reverse a queue by using a stack
 * @details
 * Using the Last In First Out property of Stacks
 * we can reverse the order of a queue
 * @author [Nikhil](https://github.com/ngiridharan)
 * @see related_file.cpp, another_file.cpp
 */



#include <iostream>
#include <queue>
#include <stack>
using std::cout;
using std::endl;
using std::queue;
using std::stack;



template <typename T>
void printQueue(queue<T>& q){
    while (!q.empty()){
        cout << q.front()<< " ";
        q.pop();
    }
    cout << endl;
}
template <typename T>
queue<T> reverseQueue(queue<T>& q){
    stack<T> s;
    queue<T> newQueue;
    while(!q.empty()){
        T temp = q.front();
        s.push(temp);
        q.pop();
    }
    while(!s.empty()){
        newQueue.push(s.top());
        s.pop();
    }
    return newQueue;
}


int main(){

    //test for ints
    queue<int> testQueueInt;
    for(int i = 0; i < 10; i++){
        testQueueInt.push(rand() % 10);
    }
    cout << "Original queue:" << endl;
    queue<int>temp = testQueueInt;
    printQueue(temp);
    cout<<"Reversed queue"<<endl;
    queue<int> rev = reverseQueue(testQueueInt);
    printQueue(rev);



    //test for chars
    queue<char> testQueueChar;
    for(int i = 0; i < 10; i++){
        testQueueChar.push(char(rand() % 100));
    }
    cout << "Original queue:" << endl;
    queue<char>tempChar = testQueueChar;
    printQueue(tempChar);
    cout<<"Reversed queue"<<endl;
    queue<char> revChar = reverseQueue(testQueueChar);
    printQueue(revChar);
}
