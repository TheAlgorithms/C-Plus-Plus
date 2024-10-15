#include <iostream>
#include <vector>
using namespace std;

// Template function to print elements
template<typename T>
void printElements(const T& element) {
    cout << element << " ";
}

// Overloaded function for vectors (recursive case)
template<typename T>
void printElements(const vector<T>& arr) {
    for (const auto& element : arr) {
        printElements(element);  // Recursive call for nested vectors
    }
}

int main() {
    // Example multi-dimensional array using vectors
    vector<vector<vector<int>>> multiDimensionalArray = {
        {{1, 2}, {3, 4}},
        {{5, 6}},
        {{7, 8}, {9}}
    };

    printElements(multiDimensionalArray);
    cout << endl;

    return 0;
}
