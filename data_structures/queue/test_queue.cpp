#include <iostream>
#include <string>

#include "./queue.h"

int main() {
    queue<std::string> q;
    std::cout << "---------------------- Test construct ----------------------"
              << std::endl;
    q.display();
    std::cout
        << "---------------------- Test isEmptyQueue ----------------------"
        << std::endl;
    if (q.isEmptyQueue())
        std::cout << "PASS" << std::endl;
    else
        std::cout << "FAIL" << std::endl;
    std::cout << "---------------------- Test enQueue ----------------------"
              << std::endl;
    std::cout << "After Hai, Jeff, Tom, Jkingston go into queue: " << std::endl;
    q.enQueue("Hai");
    q.enQueue("Jeff");
    q.enQueue("Tom");
    q.enQueue("Jkingston");
    q.display();
    std::cout << "---------------------- Test front ----------------------"
              << std::endl;
    std::string value = q.front();
    if (value == "Hai")
        std::cout << "PASS" << std::endl;
    else
        std::cout << "FAIL" << std::endl;
    std::cout << "---------------------- Test deQueue ----------------------"
              << std::endl;
    q.display();
    q.deQueue();
    q.deQueue();
    std::cout << "After Hai, Jeff left the queue: " << std::endl;
    q.display();
    return 0;
}
