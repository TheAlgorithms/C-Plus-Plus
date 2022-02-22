// Returns Sorted elements after performing Cocktail Selection Sort
// It is a Sorting algorithm which chooses the minimum and maximum element in an
// array simultaneously, and swaps it with the lowest and highest available
// position iteratively or recursively

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

// Iterative Version

void CocktailSelectionSort(std::vector<int> &vec, int low, int high) {
    while (low <= high) {
        int minimum = vec[low];
        int minimumindex = low;
        int maximum = vec[high];
        int maximumindex = high;

        for (int i = low; i <= high; i++) {
            if (vec[i] >= maximum) {
                maximum = vec[i];
                maximumindex = i;
            }
            if (vec[i] <= minimum) {
                minimum = vec[i];
                minimumindex = i;
            }
        }
        if (low != maximumindex || high != minimumindex) {
            std::swap(vec[low], vec[minimumindex]);
            std::swap(vec[high], vec[maximumindex]);
        } else {
            std::swap(vec[low], vec[high]);
        }

        low++;
        high--;
    }
}

// Recursive Version

void CocktailSelectionSort_v2(std::vector<int> &vec, int low, int high) {
    if (low >= high)
        return;

    int minimum = vec[low];
    int minimumindex = low;
    int maximum = vec[high];
    int maximumindex = high;

    for (int i = low; i <= high; i++) {
        if (vec[i] >= maximum) {
            maximum = vec[i];
            maximumindex = i;
        }
        if (vec[i] <= minimum) {
            minimum = vec[i];
            minimumindex = i;
        }
    }
    if (low != maximumindex || high != minimumindex) {
        std::swap(vec[low], vec[minimumindex]);
        std::swap(vec[high], vec[maximumindex]);
    } else {
        std::swap(vec[low], vec[high]);
    }

    CocktailSelectionSort(vec, low + 1, high - 1);
}

/**
 * @brief the function called when the user enters a either than 0/1
 *
 */
void unknown_method() { std::cerr << "Please enter [0/1] to seclect method: "; }

// main function, select any one of iterative or recursive version

int main() {
    int n;
    std::cout << "Enter number of elements\n";
    std::cin >> n;
    std::vector<int> v(n);
    std::cout << "Enter all the elements\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> v[i];
    }

    std::cout << "Enter method: \n\t0: iterative\n\t1: recursive:\t";

    int method;
    do {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> method;

        std::cin.fail() ? unknown_method()
        : method == 0   ? CocktailSelectionSort(v, 0, n - 1)
        : method == 1   ? CocktailSelectionSort_v2(v, 0, n - 1)
                        : unknown_method();
    } while (std::cin.fail() || method != 0 && method != 1);

    std::cout << "Sorted elements are\n";
    std::copy(begin(v), end(v), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}