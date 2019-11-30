// Copyright 2020 Divide-et-impera-11
#include <assert.h>
#include <iostream>
#include <string>
using namespaces std;
template<class Type> inline Type* binary_s(Type *array, size_t size, Type key) {
int32_t lower_index(0), upper_index(size - 1), middle_index;
while (lower_index <= upper_index) {
     middle_index = floor((lower_index + upper_index) / 2);
     if (*(array + middle_index) < key) lower_index = (middle_index + 1);
     else if (*(array + middle_index) > key)upper_index = (middle_index - 1);
     else  return (array + middle_index);
     }
return nullptr;
}
template<class Type> Type* Struzik_Search(Type* array, size_t size, Type key) {
  uint32_t block_front(0), block_size = size == 0 ? 0 : 1;
  while (block_front != block_size) {
        if (*(array + block_size - 1) < key) {
           block_front = block_size;
           (block_size * 2 - 1 < size) ? (block_size *= 2) : block_size = size;
           continue;
        }
  return binary_s<Type>(array + block_front, (block_size - block_front), key);
  }
return nullptr;
}
int main() {
int *sorted_array = new int[7]{7, 10, 15, 23, 70, 105, 203};
assert(Struzik_Search<int>(sorted_array, 7, 0) == nullptr);
assert(Struzik_Search<int>(sorted_array, 7, 1000) == nullptr);
assert(Struzik_Search<int>(sorted_array, 7, 50) == nullptr);
assert(Struzik_Search<int>(sorted_array, 7, 7) == sorted_array);
return EXIT_SUCCESS;
}
