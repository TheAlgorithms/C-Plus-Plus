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


struct list {
    std::array<int, 50> data{};
    int top = 0;
    bool isSorted = false;

    /*
     * search an element in the list using binaray search.
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
        int pos=0;
        for (int i = 0; i < top; i++) {
            int min = data[i];
            for (int j = i + 1; j < top; j++) {
                if (data[j] < min) {
                    pos = j;
                    min = data[pos];
                }
            }

            int temp = data[i];
            data[i] = data[pos];
            data[pos] = temp;
        }
        isSorted = true;
    }

    void insert(int x) {
        if (top == 49) {
            std::cout << "\nOverflow";
            return;
        }
        if (!isSorted) {
            data[top] = x;
            top++;
        } else {
            int pos = 0;

            for (int i = 0; i < top - 1; i++) {
                if (data[i] <= x && x <= data[i + 1]) {
                    pos = i + 1;
                    break;
                }
            }
            if (pos == 0) {
                pos = top - 1;
            }

            for (int i = top; i > pos; i--) {
                data[i] = data[i - 1];
            }
            top++;
            data[pos] = x;
        }
    }

    void Remove(int x) {
        int pos = Search(x);
        if (pos == -1) {
            std::cout << "\n Element does not present in the list ";
            std::cout << "\n Kindly enter valid input ";
        }
        std::cout << "\n" << data[pos] << " deleted";
        for (int i = pos; i < top; i++) {
            data[i] = data[i + 1];
        }
        top--;
    }

    void Show() {
        for (int i = 0; i < top; i++) {
            std::cout << data[i] << "\t";
        }
    }
};

int main() {
    list L;
    int choice;
    int x;
    do {
        // Choices for operations on the list_array.
        std::cout << "\n0.Exit";
        std::cout << "\n1.Insert";
        std::cout << "\n2.Delete";
        std::cout << "\n3.Search";
        std::cout << "\n4.Sort";
        std::cout << "\n5.Print";
        std::cout << "\n\nEnter Your Choice : ";
        std::cin >> choice;
        switch (choice) {
            case 0:
                break;
            case 1:
                std::cout << "\nEnter the element to be inserted : ";
                std::cin >> x;
                L.insert(x);
                break;
            case 2:
                std::cout << "\nEnter the element to be removed : ";
                std::cin >> x;
                L.Remove(x);
                break;
            case 3:
                std::cout << "\nEnter the element to be searched : ";
                std::cin >> x;
                L.Search(x);
                break;
            case 4:
                L.Sort();
                break;
            case 5:
                L.Show();
                break;
            default:
                std::cout << "\nplease enter valid option.";
        }
    } while (choice != 0);
    return 0;
}
