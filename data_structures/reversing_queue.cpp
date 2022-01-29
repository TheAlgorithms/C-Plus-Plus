/**
 * @file
 * @brief Reverse a queue by using a stack -
 *  (https://www.geeksforgeeks.org/reversing-a-queue/)
 * @details
 * Using the Last In First Out property of Stacks
 * we can reverse the order of a queue by pushing all entries of a queue
 * into a stack, and then popping them from the stack back onto the queue.
 * @author [Nikhil](https://github.com/ngiridharan)
 * @see related_file.cpp, another_file.cpp
 */



#include <iostream> // for all IO operations
#include <queue>    // access to the queue data structure
#include <stack>    // access to the stack data structure
using std::cout; // for all console printing
using std::endl; // alternate way to produce a new line
using std::queue; //cleanliness
using std::stack; // cleanliness



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

/**
 * @brief Main function
 * @details
 * Examples of random data being pushing into a queue and then reversed
 * are shown, with int char, and bool implementations.
 * @returns 0 on exit
 */
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


    //test for bool
    queue<bool> testQueueBool;
    for(int i = 0; i < 10; i++){
        testQueueBool.push(bool(rand() % 2));
    }
    cout << "Original queue:" << endl;
    queue<bool>tempBool = testQueueBool;
    printQueue(tempBool);
    cout<<"Reversed queue"<<endl;
    queue<bool> revBool = reverseQueue(testQueueBool);
    printQueue(revBool);




    return 0;
}
