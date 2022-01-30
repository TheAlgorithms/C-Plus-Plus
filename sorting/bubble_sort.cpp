/**
 * @file
 * @brief Bubble sort algorithm
 *
The working principle of the Bubble sort algorithm:

The bubble sorting algorithm works by "bubbling" the largest number to the top
of the list. This is done every pass until the entire set of numbers is fully
sorted. The bubbling apsect works by swapping adjacent numbers if the left
number is larger than the right number. After each adjacent number is checked
going up the list, this is considered one pass.

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

What is Recursion?

Recursion is the method of solving a problem by solving smaller instances of
that same problem. This is most commonly seen with a function calling itself
until a base case has been reached.

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
using namespace std;

void Ouput(vector<int> numbers) {
    cout << "Sorted Array : ";
    for (int i = 0; i < numbers.size(); i++) {
        if (i != numbers.size() - 1) {
            std::cout << numbers[i] << ", ";
        } else {
            cout << numbers[i] << std::endl;
        }
    }
    cout << endl;
}

vector<int> BubbleSort(vector<int> &numbers) {
    bool swap_check = true;

    for (int i = 0; (i < numbers.size()) && (swap_check); i++) {
        swap_check = false;
        for (int j = 0; j < numbers.size() - 1 - i; j++) {
            if (numbers[j] > numbers[j + 1]) {
                swap_check = true;
                swap(numbers[j], numbers[j + 1]);
            }
        }
    }
    return numbers;
}

void RecursiveBubbleSort(vector<int> &numbers, int n) {
    if (n == 1)
        return;

    for (int i = 0; i < n - 1; i++)
        if (numbers[i] > numbers[i + 1])
            swap(numbers[i], numbers[i + 1]);

    RecursiveBubbleSort(numbers, n - 1);
}

int main() {
    // Inputs
    cout << "Enter amount of numbers to sort: ";
    int n;
    cin >> n;

    cout << "Enter " << n << " numbers seperated by space: ";
    int TempNum;
    vector<int> numbers;
    for (int i = 0; i < n; i++) {
        cin >> TempNum;
        numbers.push_back(TempNum);
    }

    // which sort?
    cout << "Regular or Recursive Bubble Sort? ";
    string input;
    cin >> input;

    if (input == "Regular" || input == "regular") {
        // Bubble Sort
        BubbleSort(numbers);
        cout << "\nRegular Bubble ";
        Ouput(numbers);
    } else if (input == "Recursive" || input == "recursive") {
        // Recursive Bubble Sort:
        RecursiveBubbleSort(numbers, n);
        cout << "\nRecursive Bubble ";
        Ouput(numbers);
    }

    return 0;
}
