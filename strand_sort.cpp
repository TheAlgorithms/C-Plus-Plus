#include <stdio.h> // Only for printf function
#include <list>

using namespace std;

template <typename T>
list<T> strand_sort(list<T> lst) {
    if (lst.size() < 2) // Returns list if empty or contains only one element
        return lst;
    list<T> result;
    list<T> sorted;
    while (lst.empty() == false) {
        sorted.push_back(lst.front());
        lst.pop_front();
        for (auto it = lst.begin(); it != lst.end();) {
            if (sorted.back() <= *it) {
                sorted.push_back(*it);
                it = lst.erase(it);
            } else
                it++;
        }
        result.merge(sorted);
    }
    return result;
}

// Entry point for testing
int main() {
    list<int> lst = { -333, 525, 1, 0, 94, 52, 33 };

    printf("Before: ");
    for(auto item: lst)
        printf("%d ", item);

    lst = strand_sort(lst); // Sort list.

    printf("\nAfter: ");
    for(auto item: lst)
        printf("%d ", item);
        
    return 0;
}
