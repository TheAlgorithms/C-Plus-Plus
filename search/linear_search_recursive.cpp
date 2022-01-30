/**
* @brief [Recursive Implementation of Linear Search]
* @author [Steven Cabral]
**/

#include <iostream> //input & output services
#include <array>
#include <cassert> //




int LinearSearch(int *array, int size, int key){
    //If the last element in the array is the key, this returns its index
    if(array[size] == key){
        return size; 
    }
    //Will only execture when the array is empty and there are no elements left to search
    else if(size <= 0){
        return -1;
    }
    return LinearSearch(array, size-1, key); //recursively searches remaining elements
}
static void test() {
    /* tests search on basic arrays */
    int arrSize = 10; 
    int *arr = new int[arrSize];
    for(int i = 0; i < arrSize; i++){
        arr[i] = i*100;
        
    }
    
    assert(LinearSearch(arr, arrSize, 0) == 0); // this ensures that the algorithm works as expected
    assert(LinearSearch(arr, arrSize, 100) == 1);
    assert(LinearSearch(arr, arrSize, 900) == 9); // can have multiple checks

    
    arrSize = 100;
    int *arr2 = new int[arrSize];
    for(int i = 0; i < arrSize; i++){
        arr2[i] = i*115;
    }

    assert(LinearSearch(arr2, arrSize, 115) == 1);
    assert(LinearSearch(arr2, arrSize, 5750) == 50);

    arrSize = 3;
    int *arr3 = new int[arrSize];
    for(int i = 0; i < arrSize; i++){
        arr3[i] = i+1000;
    }
    assert(LinearSearch(arr3, arrSize, 1000) == 0);
    assert(LinearSearch(arr3, arrSize, 1002) == 2);

    std::cout << "Preliminary Tests Passed" << std::endl;
    //free up dynamically allocated memory
    delete[] arr;
    delete[] arr2;
    delete[] arr3;
}

int main(){
    
    test();
    //Allows user arrays to be created and searched    
    int arrSize = 0;
    std::cout << "Enter the size of array to be searched: ";
    std::cin.clear();
    std::cin >> arrSize;
    int *array = new int[arrSize];    
    std::cout << "Enter all " << arrSize << " numbers: ";

    for(int i = 0; i < arrSize; i++){
        std::cin >> array[i];
    }
   
    int key = 0;
    std::cout << "What number would you like to search? " << std::endl;
    std::cin >> key;
    int result = LinearSearch(array, arrSize, key);
    
    if(result == -1){
        std::cout << "Element was not found in the given array" << std::endl;
    }
    else{
        std::cout << "Your element:" << key << " was found at index " << result << std::endl; 
    }
    delete[] array;
    return 0;
}