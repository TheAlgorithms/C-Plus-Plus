#include "cll.h"

int main() {
    /* Test CLL */
    std::cout << "----------- Test construct -----------" << std::endl;
    cll list1;
    list1.display();
    std::cout << "----------- Test insert front -----------" << std::endl;
    list1.insert_front(5);
    std::cout << "After insert 5 at front: " << std::endl;
    list1.display();
    std::cout << "After insert 10 3 7 at front: " << std::endl;
    list1.insert_front(10);
    list1.insert_front(3);
    list1.insert_front(7);
    list1.display();
    std::cout << "----------- Test insert tail -----------" << std::endl;
    std::cout << "After insert 18 19 20 at tail: " << std::endl;
    list1.insert_tail(18);
    list1.insert_tail(19);
    list1.insert_tail(20);
    list1.display();
    std::cout << "----------- Test find item -----------" << std::endl;
    if (list1.find_item(10)) {
        std::cout << "PASS" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
    }
    if (!list1.find_item(30)) {
        std::cout << "PASS" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
    }
    std::cout << "----------- Test * operator -----------" << std::endl;
    int value = *list1;
    std::cout << "Value at *list1: " << value << std::endl;
    std::cout << "----------- Test ++ operator -----------" << std::endl;
    list1.display();
    ++list1;
    std::cout << "After ++list1: " << std::endl;
    list1.display();

    return 0;
}
