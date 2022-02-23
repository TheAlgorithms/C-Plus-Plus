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
 * @brief Get user's input - 0 or 1
 * 
 * @return user's option 
 */
int user_input() {
    int option{};
    do {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Please select an option 0 -> iterative or 1 -> recursive: ";
        std::cin >> option;
    } while (std::cin.fail() || option < 0 || option > 1);

    return option;
}

/**
 * @brief a function that calls the iterative or recursive version of cocktail
 * selection sort based on the users selection
 *
 * @param option input from the user
 */
void execute_method(std::vector<int> &v, int option) {
    auto last_index = v.size() - 1;
    return !option ? CocktailSelectionSort(v, 0, last_index)
                   : CocktailSelectionSort_v2(v, 0, last_index);
}

// main function, select any one of iterative or recursive version

int main() {
    std::vector<int> v{3, 2, 1, 0, 9, 5, 8, 21, 19, 9};

    execute_method(v, user_input());

    std::cout << "\nSorted elements are: ";
    std::copy(begin(v), end(v), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}