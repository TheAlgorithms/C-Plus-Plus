/**
 * @file
 * @brief A cpp program for random pivot quick sort algorithm.
 * @details Intro :
 *              - A random pivot quick sort algorithm is pretty much same as quick sort with a difference of having a logic of
 *                  selecting next pivot element from the input array.
 *              - Where in quick sort is fast, but still can give you the time complexity of O(n^2) in worst case.
 *              - To avoid hitting the time complexity of O(n^2), we use the logic of randomize the selection process of pivot
 *                  element.
 *
 *          Logic :
 *              - The logic is pretty simple, the only change is in the partitioning algorithm, which is selecting the
 *                  pivot element.
 *              - Instead of selecting the last or the first element from array for pivot we use a random index to select
 *                  pivot element.
 *              - This avoids hitting the O(n^2) time complexity in practical use cases.
 *
 * @author [Nitin Sharma](https://github.com/foo290)
 *
 */


#include <iostream>
#include <ctime>
#include <cassert>
#include <algorithm>

namespace randomPivotQuickSort {

    void showArray(int arr[], int size) {
        // Just prints the array.
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    int getRandomIndex(int start, int end) {
        // Takes the start and end indices of an array and returns a random integer between the range of those two
        // for selecting pivot element.

        srand(time(nullptr)); // Initialize random number generator.
        int randomPivotIndex = start + rand() % (end - start + 1);
        return randomPivotIndex;
    }

    void swap(int arr[], int i, int j) {
        // Nothing fancy, just a simple snippet to swap two numbers in an array.
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    int partition(int arr[], int start, int end) {
        /*
         *  A partition function which handles the partition logic of quick sort.
         *
         *      (Partition Logic) :-
         *          -> Partitions are done such as numbers lower than the "pivot" element is arranged on the left side of the "pivot",
         *              and number larger than the "pivot" element are arranged on the right part of the array.
         *
         *      (Variables) :-
         *          -> pivot : The pivot element, which is selected randomly.
         *          -> pInd  : The Partition index, which will be incremented each time a number is swapped in the if condition of for loop.
         *
         *      (Algorithm) :-
         *          -> Select the pivot element randomly using getRandomIndex() function from this namespace.
         *          -> Initialize the pInd (partition index) from the start of the array.
         *          -> Loop through the array from start to less than end. (from start to < end).
         *              (Inside the loop) :-
         *                  -> Check if the current element (arr[i]) is less than the pivot element in each iteration.
         *                  -> If current element in the iteration is less than the pivot element,
         *                      then swap the elements at current index (i) and partition index (pInd) and increment the partition index by one.
         *          -> At the end of the loop, swap the pivot element with partition index element.
         *          -> Return the partition index from the function.
         *
         *
         *    params:
         *      int arr[] : The array of integers.
         *      start     : The starting index of the array passed.
         *      end       : The ending index of the array passed.
         *
         *    returns:
         *      int
         *
         * */

        int pivot = arr[end];  // Randomly selected element will be here from caller function (quickSortRP()).
        int pInd = start;

        for (int i = start; i < end; i++) {
            if (arr[i] <= pivot) {
                swap(arr, i, pInd);  // swapping the elements from current index to pInd.
                pInd++;
            }
        }
        swap(arr, pInd, end);  // swapping the pivot element to its sorted position
        return pInd;
    }

    void quickSortRP(int arr[], int start, int end) {
        if (start < end) {
            int randomIndex = getRandomIndex(start, end);
            swap(arr, end, randomIndex);  // switching the pivot with right most bound.

            int pivotIndex = partition(arr, start, end);

            // Recursively calling
            quickSortRP(arr, start, pivotIndex - 1);
            quickSortRP(arr, pivotIndex + 1, end);
        }
    }
}

class TestCases {
private:
    template<typename T>
    void log(T msg) {
        // It's just to avoid writing cout and endl
        std::cout << msg << std::endl;
    }

public:
    TestCases() {
        log("Running Tests...");
        testCase_1();
        testCase_2();
        testCase_3();
    }

    ~TestCases() {
        log("Test Cases over!");
        log("");
    }

    void testCase_1() {
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        log("This is test case 1 for Random Pivot Quick Sort Algorithm : ");
        log("Description:");
        log("   Contains 50 elements");
        int first_arr[50]{
                9, 12, 396, 273, 151, 152, 279, 282, 24, 153, 30, 160,
                164, 423, 296, 426, 299, 43, 173, 302, 49, 53, 182, 185,
                442, 313, 189, 192, 322, 452, 199, 212, 88, 475, 222, 478,
                479, 480, 226, 485, 489, 235, 112, 371, 499, 500, 246, 247,
                123, 56
        };

        int start = 0;
        int end = 49; // length - 1

        log("Running algorithm of data of length 50 ...");
        randomPivotQuickSort::quickSortRP(first_arr, start, end);
        log("This is the sorted array : ");

        log("Checking assert expression...");
        assert(std::is_sorted(first_arr, first_arr + end));
        log("[PASS] : TEST CASE 1 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

    }

    void testCase_2() {
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        log("Description:");
        log("   Contains 500 elements");
        log("This is test case 2 for Random Pivot Quick Sort Algorithm : ");
        int first_arr[500]{
                3127, 4534, 523, 1410, 717, 4587, 4566, 2363, 1727, 3636, 1522, 3154, 1703, 4279, 1192, 489, 1993,
                2609, 2502, 1908, 1465, 4689, 3553, 377, 4892, 2130, 3110, 185, 3616, 4276, 4054, 3968, 1869, 167,
                3714, 2918, 2271, 3377, 2828, 634, 3134, 1083, 3725, 498, 331, 2309, 2162, 2596, 138, 4005, 3532,
                1723, 3660, 663, 3894, 2770, 4747, 2601, 3668, 398, 4145, 1438, 1060, 1670, 4122, 4568, 4336, 4963,
                2034, 2981, 2443, 1393, 3046, 183, 3286, 822, 1282, 1724, 3332, 651, 4310, 4883, 365, 4806, 1957, 4285,
                4716, 2022, 1284, 2994, 4346, 2508, 1627, 3412, 2490, 1178, 4869, 920, 1827, 3484, 4583, 4114, 4361,
                1567, 2370, 2352, 843, 1684, 4146, 999, 4884, 1874, 1075, 4617, 2057, 3538, 382, 1530, 3859, 1058, 3761,
                3513, 2961, 3672, 2813, 4661, 4119, 328, 1896, 2556, 2384, 3834, 3547, 2954, 4706, 4182, 4803, 3328,
                4329, 266, 2701, 1919, 2414, 559, 2588, 4311, 1226, 2422, 4590, 2001, 1749, 946, 5000, 223, 3972, 412,
                1163, 2307, 4288, 3319, 2931, 2600, 775, 3204, 3367, 686, 4556, 2019, 1330, 4573, 1726, 738, 2697, 1103,
                2726, 3999, 2407, 2341, 723, 2086, 3255, 1774, 1633, 3546, 2562, 3871, 111, 3257, 4965, 2839, 4712, 150,
                2723, 624, 1720, 3898, 3299, 3883, 2921, 4562, 3079, 4200, 1072, 592, 1335, 4495, 423, 2899, 2400, 4982,
                3137, 4975, 4071, 2631, 4973, 4300, 2280, 4240, 2235, 2754, 2696, 3558, 2212, 4307, 1996, 22, 1038,
                3493, 2060, 466, 2979, 2923, 1590, 2377, 3588, 4833, 313, 193, 2381, 4032, 2483, 882, 4226, 3095, 29,
                1588, 2215, 3667, 2679, 2, 3598, 567, 4727, 4997, 4976, 1471, 79, 1201, 4040, 4749, 2206, 874, 2465,
                4248, 1965, 2892, 2189, 3269, 1939, 4497, 6, 1641, 4597, 2543, 3635, 4655, 3068, 4998, 505, 1645, 2010,
                637, 1097, 3329, 392, 270, 3734, 4293, 2725, 3496, 34, 881, 28, 12, 500, 3639, 4210, 767, 726, 3456,
                1586, 420, 2855, 690, 3417, 3501, 2510, 4779, 1014, 4462, 404, 3323, 182, 4782, 4011, 4352, 62, 4321,
                2671, 4899, 4901, 4860, 656, 4353, 602, 334, 3671, 3458, 2124, 808, 1830, 4548, 4452, 1877, 4127, 934,
                581, 238, 1409, 4391, 3140, 4157, 1963, 4018, 2983, 2015, 387, 1499, 1636, 2871, 2593, 4541, 2520, 770,
                1275, 3279, 3610, 2401, 3512, 2853, 4271, 4687, 1585, 2829, 3389, 4692, 1687, 3674, 1450, 4217, 4521,
                3882, 3096, 4350, 4238, 1850, 3111, 4697, 610, 4477, 901, 213, 3965, 4526, 889, 2351, 521, 3721, 4314,
                474, 1526, 1947, 4648, 1261, 2819, 100, 2602, 2030, 2353, 4453, 1978, 1508, 3932, 2880, 4355, 451, 3608,
                86, 1181, 1855, 1517, 3156, 468, 2900, 501, 3663, 947, 4602, 3429, 749, 1686, 1704, 554, 1760, 3934,
                2459, 959, 2249, 4126, 1441, 2632, 1569, 184, 1216, 4826, 19, 4816, 3730, 1121, 1206, 800, 1031, 2518,
                3383, 1003, 14, 4415, 277, 3924, 1777, 2392, 165, 3870, 3280, 4643, 2137, 4662, 3510, 2910, 289, 4473,
                2221, 3850, 1315, 403, 2098, 274, 3519, 2323, 3764, 491, 4035, 850, 3879, 3568, 1561, 3426, 4682, 4144,
                3433, 2711, 1400, 1752, 1885, 1107, 1881, 3921, 253, 2343, 1456, 969, 1036, 1306, 4233, 1854, 864, 2118,
                1125, 4253, 652
        };

        int start = 0;
        int end = 499; // length - 1

        log("Running algorithm of data of length 500 ...");
        randomPivotQuickSort::quickSortRP(first_arr, start, end);
        log("This is the sorted array : ");

        log("Checking assert expression...");
        assert(std::is_sorted(first_arr, first_arr + end));
        log("[PASS] : TEST CASE 2 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }

    void testCase_3() {
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        log("This is test case 3 for Random Pivot Quick Sort Algorithm : ");
        log("Description:");
        log("   Contains -ve and 0 and repeated elements");
        int first_arr[15]{
                1410, 717, 4587, 4566, 2363, 1727, 3636, 1522, 3154, 1703, 4279, 1192, 489, 2, 2
        };

        int start = 0;
        int end = 14; // length - 1

        log("Running algorithm of data of length 500 ...");
        randomPivotQuickSort::quickSortRP(first_arr, start, end);
        log("This is the sorted array : ");

        log("Checking assert expression...");
        assert(std::is_sorted(first_arr, first_arr + end));
        log("[PASS] : TEST CASE 2 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }

};


void testsDriver() {
    // Test cases called in constructor of the class.
    TestCases tc = TestCases();
}

int main() {
    // Tests driver call
    testsDriver();

    // Running Main algo
    int arr[10] = {3, 4, 0, 2, 1, 44, 7, 9, 5, 78};
    int length = sizeof(arr) / sizeof(arr[0]);
    randomPivotQuickSort::quickSortRP(arr, 0, length - 1);
    std::cout << "Sorted array is : " << std::endl;
    randomPivotQuickSort::showArray(arr, length);
}

