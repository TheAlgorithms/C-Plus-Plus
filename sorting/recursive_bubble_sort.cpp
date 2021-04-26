/**
 * @file
 * @brief Recursive Bubble sort algorithm
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

Recursion

While the recursive method does not necessarily have advantages over iterative
versions, but it is useful to enhance the understanding of the algorithm and
recursion itself. In Recursive Bubble sort algorithm, we firstly call the
function on the entire array, and for every subsequent function call, we exclude
the last element. This fixes the last element for that sub-array.Formally, for
`ith` iteration, we consider elements up to n-i, where n is the number of
elements in the array. Exit condition: n==1; i.e. the sub-array contains only
one element.

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

#include <iostream>
#include <vector>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void recursive_bubble_sort(std::vector<int> *nums, int n) {
    if (n == 1) {
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        if ((*nums)[i] > (*nums)[i + 1]) {
            swap(&(*nums)[i], &(*nums)[i + 1]);
        }
    }

    recursive_bubble_sort(nums, n - 1);
}

int main() {
    int n = 0;
    bool swap_check = true;
    std::cout << "Enter the amount of numbers to sort: ";
    std::cin >> n;
    std::vector<int> numbers;
    std::cout << "Enter " << n << " numbers: ";
    int num = 0;

    // Input
    for (int i = 0; i < n; i++) {
        std::cin >> num;
        numbers.push_back(num);
    }

    // Function call
    recursive_bubble_sort(&numbers, n);

    // Output
    std::cout << "\nSorted Array : ";
    for (int i = 0; i < numbers.size(); i++) {
        if (i != numbers.size() - 1) {
            std::cout << numbers[i] << ", ";
        } else {
            std::cout << numbers[i] << std::endl;
        }
    }
    return 0;
}
