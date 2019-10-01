#include <algorithm>
#include <iostream>

bool isSorted(int* array, int size) {
  for (int i = 0; i < size - 1; i++) {
    if (array[i] > array[i + 1]) {
      return false;
    }
  }
  return true;
}

int main() {
  int numbers_size = 10;
  int numbers[10] = {4, 3, 2, 4, 1, 8, 2, 3, 1, 2};
  while (!isSorted(numbers, numbers_size)) {
    std::random_shuffle(std::begin(numbers), std::end(numbers));
  }
  for (int i = 0; i < numbers_size; i++) {
    std::cout << numbers[i] << " ";
  }
  return 0;
}
