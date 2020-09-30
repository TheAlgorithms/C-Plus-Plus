/**
 * @file
 * @author [Tuan Ho](https://github.com/ttuanho)
 * @brief Implementation of [Priority
 * queue](https://en.wikipedia.org/wiki/Priority_queue) an abstract data type
 * similar to regular queue or stack data structure in which each element
 * additionally has a "priority" associated with it.
 * \todo Add more edge test cases:
 * <ul>
 *  <li> 
 *      Handling the case where there's duplicated priority.
 *  </li>
 * </ul>
 * @note
 * @see test_queue.c
 */

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

#include "./priority_queue.h"

int main() {
    queue<string, Priority> q;
    cout << "---------------------- Test construct ----------------------"
              << endl;
    q.display();
    cout << "PASS" << endl;
    cout
        << "---------------------- Test isEmptyQueue ----------------------"
        << endl;
    assert(q.isEmptyQueue());
    cout << "PASS" << endl;
        
    cout << "---------------------- Test insert & front() & last() ----------------------"
              << endl;
    cout << "Insert (A,2), (B,0), (C,3), (D,1) into queue: " << endl;
    q.insert("A",2);
    assert(q.front()->data == "A");
    assert(q.front()->prior == 2);
    q.insert("B", 0);
    assert(q.last()->data == "B");
    assert(q.last()->prior == 0);
    q.insert("C",3);
    assert(q.last()->data == "C");
    assert(q.last()->prior == 3);
    q.insert("D",1);
    q.display();
    assert(q.getSize() == 4);
    cout << "PASS" << endl;
    cout << "---------------------- Test front ----------------------"
              << endl;
    string value = q.frontData();
    assert(value == "A");
    cout << "PASS" << endl;

    cout << "---------------------- Test deQueue ----------------------"
              << endl;
    q.display();
    node<string, Priority> *remove1 = q.deQueue();
    assert(remove1->data == "C");
    assert(remove1->prior == 3);
    assert(q.getSize() == 3);

    node<string, Priority> *remove2 = q.deQueue();
    assert(remove1->data == "A");
    assert(remove1->prior == 2);
    assert(q.getSize() == 2);
    
    
    cout << "After (A,2), (C,3) left the queue: " << endl;
    q.display();
    cout << "PASS" << endl;
    return 0;
}

