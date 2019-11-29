#include <iostream>
#include <string>
#include <assert.h>
using namespaces std;
/*-----------------Binary Search Algorithm(use by struzik algorithm)-----------------
Time Complexity O(log n) where 'n' is the number of elements
Worst Time Complexity O(log n)
Best Time Complexity O(1)
Space Complexity O(1)
Auxiliary Space Complexity O(1)*/
template<class Type> inline Type* binary_search(Type *array, size_t size, Type key) { // Parameter List:Pointer to and array|size of array|key what you search
        int32_t lower_index(0), upper_index(size - 1),middle_index; // lower_index => start of search range | upper_index => end of search range | middle_index => middle of search range
        while (lower_index <= upper_index)
        {
                middle_index = floor((lower_index + upper_index) / 2);
                if (*(array + middle_index) < key) lower_index = (middle_index + 1); // if the key is smaller than the middle of search range, we narrow the search range from up
                else if (*(array + middle_index) > key) upper_index = (middle_index - 1); // if the key is bigger than the middle of search range, we narrow the search range from down
                else return (array + middle_index); // the key has been found
        }
        return nullptr;
}
/*-----------------Struzik Search Algorithm(Exponential)-----------------
Time Complexity O(log i)where i is the position of the search key in the list
Worst Time Complexity O(log i)
Best Time Complexity O(1)
Space Complexity O(1)
Auxiliary Space Complexity O(1)*/
template<class Type> Type* Struzik_Search(Type* array,size_t size,Type key) { // Parameter List: Pointer to an array(sorted)!You can use complex objectum, but in that case you have to overload '<>' operators!|size of array|key what you search
        uint32_t block_front(0),block_size = size == 0 ? 0 : 1; // the start and end of the first block where the algorithm starts seach !if the size of array 0 than return null pointer
        while (block_front != block_size) // when the start of block(block_front) and end of block(block_size) equal it means the key bigger than the last element of array and it return null pointer
        {
                if (*(array + block_size - 1) < key) { // if the key is bigger than the end of block we define a new block what is twice bigger than the previous
                        block_front = block_size;
                        (block_size * 2 - 1 < size) ? (block_size *= 2) : block_size = size; // if the end of new block bigger than size of array it takes the end of array
                        continue;
                }
                // when the algorithm delimit the block where the key shold be we do a binary search there
                return binary_search<Type>(array + block_front, (block_size - block_front), key);
        }
        return nullptr;
}
int main(){
        int *sorted_array = new int[7]{ 7,10,15,23,70,105,203 };
        assert(Struzik_Search<int>(sorted_array, 7, 0) == nullptr);
        assert(Struzik_Search<int>(sorted_array, 7, 1000) == nullptr);
        assert(Struzik_Search<int>(sorted_array, 7, 50) == nullptr);
        assert(Struzik_Search<int>(sorted_array, 7, 7) == sorted_array);
   return EXIT_SUCCESS;
}
// Copyright 2019 Molnár Mihály
