/**
 * @file
 * @brief Bubble sort algorithm
 *
 * The working principle of the Bubble sort algorithm:

Bubble sort algorithm is the bubble sorting algorithm. The most important reason
for calling the bubble is that the largest number is thrown at the end of this
algorithm. This is all about the logic. In each iteration, the largest number is
expired and when iterations are completed, the sorting takes place.

What is Swap?

Swap in the software means that two variables are displaced.
An additional variable is required for this operation. x = 5, y = 10.
We want x = 10, y = 5. Here we create the most variable to do it.

int z;
z = x;
x = y;
y = z;

The above process is a typical displacement process.
When x assigns the value to x, the old value of x is lost.
That's why we created a variable z to create the first value of the value of x,
and finally, we have assigned to y.

Bubble Sort Algorithm Analysis (Best Case - Worst Case - Average Case)

Bubble Sort Worst Case Performance is O (n²). Why is that? Because if you
remember Big O Notation, we were calculating the complexity of the algorithms in
the nested loops. The n * (n - 1) product gives us O (n²) performance. In the
worst case all the steps of the cycle will occur. Bubble Sort (Avarage Case)
Performance. Bubble Sort is not an optimal algorithm. in average, O (n²)
performance is taken. Bubble Sort Best Case Performance. O (n). However, you
can't get the best status in the code we shared above. This happens on the
optimized bubble sort algorithm. It's right down there.
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

namespace sorting {

// Bubble Sorting using array
template <typename T>
void bubbleSort(T *arr, int n) {
    bool swap_check = true;
    for (int i = 0; (i < n) && (swap_check); i++) {
        swap_check = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap_check = true;
                std::swap(arr[j],
                          arr[j + 1]);  // by changing swap location.
                                        // I mean, j. If the number is
                                        // greater than j + 1, then it
                                        // means the location.
            }
        }
    }
}

// Bubble Sorting using vector
template <typename T>
void bubbleSort(std::vector<T> *arr) {
    size_t n = arr->size();
    bool swap_check = true;
    for (size_t i = 0; (i < n) && (swap_check); i++) {
        swap_check = false;
        for (size_t j = 0; j < n - 1 - i; j++) {
            if (arr[0][j] > arr[0][j + 1]) {
                swap_check = true;
                std::swap(arr[0][j], arr[0][j + 1]);
                // by changing swap location.
                // I mean, j. If the number is
                // greater than j + 1, then it
                // means the location.
            }
        }
    }
}
}  // namespace sorting
// namespace sorting

// Test Case to test algorithm
void tests() {
    // positive case
    int arr1[10] = {10, 99, 56, 8, 128, 1, 76, 48, 300, 4};
    std::cout << "Test 1... ";
    sorting::bubbleSort(arr1, 10);
    assert(std::is_sorted(arr1, arr1 + 10));
    std::cout << "passed" << '\n';

    // negative case
    int arr2[8] = {-55, -20, -5, -77, -12, -45, -32, -10};
    std::cout << "Test 2... ";
    sorting::bubbleSort(arr2, 8);
    assert(std::is_sorted(arr2, arr2 + 8));
    std::cout << "passed" << '\n';

    // mix positive and negative
    int arr3[8] = {1028, 45, -60, 0, -14, 35, 7, -4};
    std::cout << "Test 3... ";
    sorting::bubbleSort(arr3, 8);
    assert(std::is_sorted(arr3, arr3 + 8));
    std::cout << "passed" << '\n';

    // float
    float arr4[8] = {4.0, -7.4, 0, 17.5, -2.3, 6.4, 1.5, -6.6};
    std::cout << "Test 4... ";
    sorting::bubbleSort(arr4, 8);
    assert(std::is_sorted(arr4, arr4 + 8));
    std::cout << "passed" << '\n';

    // using vector
    std::vector<float> arr5({4.0, -7.4, 0, 17.5, -2.3, 6.4, 1.5, -6.6});
    std::cout << "Test 5... ";
    sorting::bubbleSort(&arr5);
    assert(std::is_sorted(std::begin(arr5), std::end(arr5)));
    std::cout << "passed" << std::endl;
}

// Main Fuction
int main() {
    // Running tests to test algorithm
    tests();

    // For user interaction
    size_t n;
    std::cout << "Enter the length of array (0 to exit)";
    std::cin >> n;

    if (n == 0) {
        return 0;
    }

    int *arr = new int[n];
    std::cout << "Enter any" << n << "Numbers for Unsorted Array : ";

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    sorting::bubbleSort(arr, n);

    std::cout << "\nSorted Array : ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';

    delete[] arr;
    return 0;
}