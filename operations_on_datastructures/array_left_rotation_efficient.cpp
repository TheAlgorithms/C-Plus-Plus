#include <iostream>
/**
 * This program can be used to rotate an array d times towards left.
 * Variables used:
 * size         : Size of the Array.
 * no_of_rotate : Number of indices you want to rotate.
 * arr          : Used to copy first no_of_rotate elements of the array.
 * a            : Main array used.
 * i            : Loop variable.
 * j            : Loop variable.
 *
 * This program uses a more efficient logic to rotate the array as each element
 * is roated d times in only single iteration. This uses less time for more long
 * arrays. */


void rotateArray(int * a,int size, int no_of_rotate){  //Rotating the Array
    int *arr = new int[no_of_rotate];
    for (int i = 0; i < no_of_rotate; i++) {
        arr[i] = a[i];
    }
    int j = 0;
    for (int i = no_of_rotate; i < size; i++) {
        a[j] = a[i];
        j++;
    }
    j = 0;
    for (int i = size - no_of_rotate; i < size; i++) {
        a[i] = arr[j];
        j++;
    }
}

void printArray(int * a, int size){  //Printing the Array
   for (int j = 0; j < size; j++) {
        std::cout << a[j] << " ";
    }
    std::cout << "\n"; 
}

int main() {
    int size, no_of_rotate;
    std::cout << "Enter size of array=";
    std::cin >> size;
    std::cout << "Enter Number of indeces u want to rotate the array to left=";
    std::cin >> no_of_rotate;
    int *a = new int[size];
    std::cout << "Enter elements of array(seprated by space)=";
    for (int i = 0; i < size; i++) {
        std::cin >> a[i];
    }

    rotateArray(a,size,no_of_rotate);
  
    std::cout << "Your rotated array is=";
    printArray(a,size);
    return 0;
}

/**
 * The Algorithm used is:
 * 1) Input array, size, and no of times to rotate.
 * 2) Create a new array and save first no_of_rotate elements into it.
 * 3) Copy the remaining elements from starting index of the input array.
 * 4) Copy back the elements saved in the new array to the input array.
 * 5) Print the array. */