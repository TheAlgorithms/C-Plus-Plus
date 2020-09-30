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

#include "./priority_queue.h"

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    queue<std::string, Priority> q;
    std::cout << "---------------------- Test construct ----------------------"
              << std::endl;
    q.display();
    std::cout << "PASS" << std::endl;
    std::cout
        << "---------------------- Test isEmptyQueue ----------------------"
        << std::endl;
    assert(q.isEmptyQueue());
    std::cout << "PASS" << std::endl;
        
    std::cout << "---------------------- Test insert & front() & last() ----------------------"
              << std::endl;
    std::cout << "Insert (A,2), (B,0), (C,3), (D,1) into queue: " << std::endl;
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
    assert(q.last()->data == "D");
    assert(q.last()->prior == 1);
    q.display();
    assert(q.getSize() == 4);
    std::cout << "PASS" << std::endl;
    std::cout << "---------------------- Test front ----------------------"
              << std::endl;
    std::string value = q.frontData();
    assert(value == "A");
    std::cout << "PASS" << std::endl;

    std::cout << "---------------------- Test deQueue ----------------------"
              << std::endl;
    q.display();
    node<std::string, Priority> *remove1 = q.deQueue();
    assert(remove1->data == "C");
    assert(remove1->prior == 3);
    assert(q.getSize() == 3);

    node<std::string, Priority> *remove2 = q.deQueue();
    assert(remove2->data == "A");
    assert(remove2->prior == 2);
    assert(q.getSize() == 2);
    
    
    std::cout << "After (A,2), (C,3) left the queue: " << std::endl;
    q.display();
    std::cout << "PASS" << std::endl;
    return 0;
}
