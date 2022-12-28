#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

/*--------------------------------------------------------------------------
/Iterate through the array from both sides to find the index of search_item.
/
/:param array: the array to be searched
/:param search_item: the item to be searched
/:return the index of search_item, if search_item is in array, else -1
/
/ Examples:
/ >>> double_linear_search([1, 5, 5, 10], 1)
/ 0
/ >>> double_linear_search([1, 5, 5, 10], 5)
/ 1
/ >>> double_linear_search([1, 5, 5, 10], 100)
/ -1
/ >>> double_linear_search([1, 5, 5, 10], 10)
/ 3
/--------------------------------------------------------------------------*/
int double_linear_search(std::vector<int> list, int search_item) {
    // define the start and end index of the given array
    int start_ind = 0;
    int end_ind = static_cast<int>(list.size() - 1);
    while (start_ind <= end_ind) {
        if (list[start_ind] == search_item) {
            return start_ind;
        } else if (list[end_ind] == search_item) {
            return end_ind;
        }
        start_ind += 1;
        end_ind -= 1;
    }
    return -1;
}

void test(std::vector<int> list, int number, int expected) {
    auto result = double_linear_search(std::move(list), number);
    std::cout << "Expected value" << expected << " in search for " << number
              << ":\t" << (result == expected ? "PASS" : "FAIL") << std::endl;
}

int main() {
    // Main Test
    std::vector<int> large_list(100);
    std::iota(std::begin(large_list), std::end(large_list), 0);
    test(large_list, 40, 40);

    // Additional Testing
    std::vector<int> short_list = {1, 5, 5, 10};
    test(short_list, 1, 0);
    test(short_list, 5, 1);
    test(short_list, 100, -1);
    test(short_list, 10, 3);
}
