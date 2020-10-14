/*Author Alok Khulbay
Date:12/10/2020.
*/
#include <iostream>
#include <deque>
#include <string>
#include <cstdlib>
#include <vector>
int main()
{
    std::deque<int> d;
    std::deque<int>::iterator it;
    int c = 0, item = 0;
    while (1)
    {
        std::cout << "1.Size of the Deque" << std::endl;
        std::cout << "2.Insert Element at the End" << std::endl;
        std::cout << "3.Insert Element at the Front" << std::endl;
        std::cout << "4.Delete Element at the End" << std::endl;
        std::cout << "5.Delete Element at the Front" << std::endl;
        std::cout << "6.Front Element at the Deque" << std::endl;
        std::cout << "7.Last Element at the Deque" << std::endl;
        std::cout << "8.Display Deque" << std::endl;
        std::cout << "9.Exit" << std::endl;
        std::cout << "Enter your choice:";
        std::cin >> c;
        switch (c)
        {
        case 1:
            std::cout << "Size of the Deque: " << d.size() << std::endl;
            break;
        case 2:
            std::cout << "Enter value to be inserted at the End: " << std::endl;
            std::cin >> item;
            d.push_back(item);
            break;
        case 3:
            std::cout << "Enter value to be inserted at the Front: " << std::endl;
            std::cin >> item;
            d.push_front(item);
            break;
        case 4:
            item = d.back();
            d.pop_back();
            std::cout << "Element " << item << " Deleted" << std::endl;
            break;
        case 5:
            item = d.front();
            d.pop_front();
            std::cout << "Element " << item << "Deleted" << std::endl;
            break;
        case 6:
            std::cout << "Front Element of the Deque is: ";
            std::cout << d.front() << std::endl;
            break;
        case 7:
            std::cout << "Back Element of the Deque is: ";
            std::cout << d.back() << std::endl;
            break;
        case 8:
            std::cout << "Elements of Deque: ";
            for (it = d.begin(); it != d.end(); it++)
            {
                std::cout << *it << " ";
                std::cout << std::endl;
            }
            break;
        case 9:
            exit(1);
            break;

        default:
            std::cout << "Wrong Choice" << std::endl;
        }
    }
    return 0;
}