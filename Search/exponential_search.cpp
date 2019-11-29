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
template<class Type> inline Type* binary_search(Type *array, size_t size, Type key) {
        int32_t lower_index(0), upper_index(size - 1),middle_index;
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
template<class Type> Type* Struzik_Search(Type* array,size_t size,Type key) {
        uint32_t block_front(0),block_size = size == 0 ? 0 : 1;
        while (block_front != block_size)
        {
                if (*(array + block_size - 1) < key) {
                        block_front = block_size;
                        (block_size * 2 - 1 < size) ? (block_size *= 2) : block_size = size;
                        continue;
                }
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
      return 0;
}
