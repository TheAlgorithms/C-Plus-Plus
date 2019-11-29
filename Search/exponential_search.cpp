#include <iostream>
#include <string>
#include <assert.h>
using namespaces std;
//-----------------Binary Search Algorithm(use by Struzik algorithm)-----------------
// Time Complexity O(log n) where 'n' is the number of elements
// Worst Time Complexity O(log n)
// Best Time Complexity O(1)
// Space Complexity O(1)
// Auxiliary Space Complexity O(1)
template<class Type> inline Type* binary_search(Type *array, size_t size, Type key) {//Parameter List:Pointer to an array|size of array|key what you search
        int32_t lower_index(0), upper_index(size - 1),middle_index; //lower_index => start of search range|upper_index => end of search range
        while (lower_index <= upper_index)
        {
                middle_index = floor((lower_index + upper_index) / 2);
                if (*(array + middle_index) < key) lower_index = (middle_index + 1); //narrow the search range from up
                else if (*(array + middle_index) > key) upper_index = (middle_index - 1);//narrow the search range from down
                else return (array + middle_index); //key has been found
        }
        return nullptr;
}
//-----------------Struzik Search Algorithm(Exponential)-----------------
// Time Complexity O(log i)where i is the position of the search key in the list
// Worst Time Complexity O(log i)
// Best Time Complexity O(1)
// Space Complexity O(1)
// Auxiliary Space Complexity O(1)
template<class Type> Type* Struzik_Search(Type* array,size_t size,Type key) { // Parameter List:Pointer to an array|size of array|key what you search
        uint32_t block_front(0),block_size = size == 0 ? 0 : 1; //block_front => start of search range|block_size => end of search range
        while (block_front != block_size) //if key bigger than last element itt will be equal and return nullptr
        {
                if (*(array + block_size - 1) < key) {//if the key is bigger than the end of block we define a new block what is twice bigger than the previous
                        block_front = block_size;
                        (block_size * 2 - 1 < size) ? (block_size *= 2) : block_size = size;//if the end of new block bigger than size of array it takes the end of array
                        continue;
                }
                return binary_search<Type>(array + block_front, (block_size - block_front), key);//if delimit the block where the key shold be,do binary search
        }
        return nullptr;
}
int main(){
    // ----------------TEST CASES----------------
        int *sorted_array = new int[7]{ 7,10,15,23,70,105,203 };
        assert(Struzik_Search<int>(sorted_array, 7, 0) == nullptr);// Key smaller than the first element of array
        assert(Struzik_Search<int>(sorted_array, 7, 1000) == nullptr);// Key bigger than the last element of array
        assert(Struzik_Search<int>(sorted_array, 7, 50) == nullptr);// Key between the elemenets of array
        assert(Struzik_Search<int>(sorted_array, 7, 7) == sorted_array);// Key is in the array !FOUND!
    // ----------------TEST CASES----------------
   return EXIT_SUCCESS;
}
