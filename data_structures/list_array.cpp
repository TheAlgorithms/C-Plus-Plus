/**
 * @file list_array.cpp
 * @brief Implementation of list_array
 * @warning The sorting algorithm is erroneous
 *
 * @details
 * The list_array is the implementation of list represented using array.
 * We can perform basic CRUD operations as well as other operations like sorting etc.
 *
 * ### Algorithm
 * It implements various method like insert, sort, search etc. efficiently.
 * You can select the operation and methods will do the rest work for you.
 * You can insert element, sort them in order, search efficiently, delete values and print the list.
 */
#include <iostream>
#include <array>
#include <cassert>

/*
 * structure of List with supporting methods.
 */
struct list {
    std::array<int, 50> data{}; // Array that implement list
    int top = 0; // Pointer to the last element
    bool isSorted = false; // indicator whether list is sorted or not
    /*
     * search an element in the list using binaraySearch.
     * @param dataArr - list
     * @param first - pointer to the first element in the remaining list
     * @param last - pointer to the last element in the remaining list
     * @param val - element that will be searched
     * @return index of element in the list if present else -1
     */
    int BinarySearch(const std::array<int, 50>& dataArr, int first, int last, int val) {
        // If both pointer cross each other means no element present in the list which is equal to the val
        if (last < first) {
            return -1;
        }
        int mid = (first + last) / 2;
        // check whether current mid pointer value is equal to element or not
        if (dataArr[mid] == val)
            return mid;
        // if current mid value is greater than  element we have to search in first half
        else if (val < dataArr[mid])
            return (BinarySearch(dataArr, first, mid - 1, val));
        // if current mid value is greater than  element we have to search in second half
        else if (val > dataArr[mid])
            return (BinarySearch(dataArr, mid + 1, last, val));

        std::cerr << __func__ << ":" << __LINE__ << ": Undefined condition\n";
        return -1;
    }
    /*
     * search an element using linear search
     * @param dataArr - list
     * @param val - element that will be searched
     * @return index of element in the list if present else -1
     */
    int LinearSearch(const std::array<int, 50>& dataArr, int x) const {
        // Going through each element in the list
        for (int i = 0; i < top; i++) {
            if (dataArr[i] == x) {
                return i; // element found at ith index
            }
        }
        // element does not present in the list
        return -1;
    }
    /*
     * parent function of binarySearch and linearSearch methods
     * @param val - element that will be searched
     * @return index of element in the list if present else -1
     */
    int Search(int val) {
        int pos; // pos variable to store index value of element.
        // if list is sorted, binary search works efficiently else linear search is the only option
        if (isSorted) {
            pos = BinarySearch(data, 0, top - 1, val);
        } else {
            pos = LinearSearch(data, val);
        }
        // if index is equal to -1 means element does not present
        // else print the index of that element
        if (pos != -1) {
            std::cout << "\nElement found at position : " << pos;
        } else {
            std::cout << "\nElement not found";
        }
        // return the index of element or -1.
        return pos;
    }
    /*
     * sort the list
     */
    void Sort() {
        int pos=0; // Initialize the index variable with starting index
        //Going through each element in the list
        for (int i = 0; i < top; i++) {
            int min = data[i]; // Initialize the min variable
            for (int j = i + 1; j < top; j++) {
                // check whether any element less than current min value
                if (data[j] < min) {
                    pos = j; // update index accordingly
                    min = data[pos]; // update minimum variable accordingly
                }
            }
            // swap min value and current element at ith index
            int temp = data[i];
            data[i] = data[pos];
            data[pos] = temp;
        }
        // mark isSorted variable as true
        isSorted = true;
    }

    /*
     * Insert the new element in the list
     * @param val - element that will be inserted
     */
    void insert(int val) {
        // overflow check
        if (top == 49) {
            std::cout << "\nOverflow";
            return;
        }
        // if list is not sorted, insert at the last
        // otherwise place it to correct position
        if (!isSorted) {
            data[top] = val;
            top++;
        } else {
            int pos = 0; // Initialize the index variable
            // Going through each element and find correct position for element
            for (int i = 0; i < top - 1; i++) {
                // check for the correct position
                if (data[i] <= val && val <= data[i + 1]) {
                    pos = i + 1; // assign correct pos to the index var
                    break; // to get out from the loop
                }
            }
            // if all elements are smaller than the element
            if (pos == 0) {
                pos = top - 1;
            }
            // shift all element to make a room for new element
            for (int i = top; i > pos; i--) {
                data[i] = data[i - 1];
            }
            top++; // Increment the value of top.
            data[pos] = val; // Assign the value to the correct index in the array
        }
    }

    /*
     * To remove the element from the list
     * @param val - element that will be removed
     */
    void Remove(int val) {
        int pos = Search(val); // search the index of the value
        // if search returns -1, element does not present in the list
        if (pos == -1) {
            std::cout << "\n Element does not present in the list ";
            std::cout << "\n Kindly enter valid input ";
            return;
        }
        // shift all the element 1 left to fill vacant space
        for (int i = pos; i < top; i++) {
            data[i] = data[i + 1];
        }
        top--; // decrement the top variable to maintain last index
        std::cout << "\n" << data[pos] << " deleted"; // print the appropriate message
    }

    /*
     * To print the list
     */
    void Show() {
        // Going through each element in the list
        for (int i = 0; i < top; i++) {
            std::cout << data[i] << "\t"; // print the element
        }
    }
};


int main() {
    // Testing
//    test();
    return 0;
}
