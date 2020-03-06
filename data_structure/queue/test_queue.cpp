#include <iostream>
#include <string>
#include "queue.h"
#include "queue.cpp"

using namespace std;

int main()
{
    queue<string> q;
    cout << "---------------------- Test construct ----------------------" << endl;
    q.display();
    cout << "---------------------- Test isEmptyQueue ----------------------" << endl;
    if(q.isEmptyQueue())
        cout << "PASS" <<endl;
    else
        cout << "FAIL" <<endl;
    cout << "---------------------- Test enQueue ----------------------" << endl;
    cout << "After Hai, Jeff, Tom, Jkingston go into queue: "<<endl;
    q.enQueue("Hai");
    q.enQueue("Jeff");
    q.enQueue("Tom");
    q.enQueue("Jkingston");
    q.display();
    cout << "---------------------- Test front ----------------------" << endl;
    string value = q.front();
    if (value == "Hai")
        cout << "PASS" <<endl;
    else
        cout << "FAIL" <<endl;
    cout << "---------------------- Test deQueue ----------------------" << endl;
    q.display();
    q.deQueue();
    q.deQueue();
    cout << "After Hai, Jeff left the queue: "<< endl;
    q.display();
    return 0;
}
