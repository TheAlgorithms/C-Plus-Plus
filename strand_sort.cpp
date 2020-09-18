#include <iostream>
#include <list>

template <typename T>
std::list<T> strand_sort(std::list<T> lst) {
    if (lst.size() < 2) { // Returns list if empty or contains only one element
        return lst;
    }
    std::list<T> result;
    std::list<T> sorted;
    while(!lst.empty()) {
        sorted.push_back(lst.front());
        lst.pop_front();
        for (typename std::list<T>::iterator it = lst.begin(); it != lst.end(); ) {
            if (sorted.back() <= *it) {
                sorted.push_back(*it);
                it = lst.erase(it);
            } else {
                it++;
            }
        }
        result.merge(sorted);
    }
    return result;
}

// Entry point for testing
int main() {
    std::list<int> lst = { -333, 525, 1, 0, 94, 52, 33 };

    std::cout << "Before: ";
    for(int item: lst) {
        std::cout << item << " ";
    }

    lst = strand_sort(lst); // Sort list.

    std::cout << "\nAfter: ";
    for(int item: lst) {
        std::cout << item << " ";
    }

    return 0;
}
