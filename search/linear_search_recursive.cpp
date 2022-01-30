/**
* @brief [Recursive Implementation of Linear Search]
* @author [Steven Cabral]
**/

#include <iostream> //input & output services

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

int main(){
    //Allows user arrays to be created and searched
    int arrSize = 0;
    std::cout << "Enter the size of array to be searched: ";
    std::cin >> arrSize;

    if(arrSize <= 0){
        std::cout << "Array size must be greater than 0, please select a new size" << std::endl;
        std::cin >> arrSize;
    }

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