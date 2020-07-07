#include <iostream>
#include <vector>

/*
Input: a sorted array and a value
Output: if the array contains the value, returns its index (index of its first occurence)
        else returns -1
*/

int min(int first, int second){
    if(first < second){
        return first;
    } else {
        return second;
    }
}

int fibonacci_search(std::vector<int> arr, int value){
    int last = 0, current = 1, offset = -1, index;
    int length = arr.size();
    int next = last + current;

    while(next < length){
        last = current;
        current = next;
        next = last + current;
    }

    while(next > 1){
        index = min(offset + last, length-1);
        if(arr[index] < value){
            next = current;
            current = last;
            last = next - current;
            offset = index;
        } else if(arr[index] > value){
            next = last;
            current = current - last;
            last = next - current;
        } else {
            return index;
        }
    }
    if(current && !arr.empty() && arr[offset+1] == value){
        return offset+1;
    }
    return -1;
}

int main() {
    int size, value;
    std::cout << "Enter size of a sorted array: " << std::endl;
    std::cin >> size;
    std::cout << "Enter array elements: " << std::endl;

    std::vector<int> arr(size);
    for(int i = 0; i < size; i++){
        std::cin >> arr[i];
    }
    std::cout << "Enter the value you're looking for: " << std::endl;
    std::cin >> value;
    int index = fibonacci_search(arr, value);
    if(index != -1){
        std::cout << "Index of the given value is " << index << std::endl;
    } else {
        std::cout << "Array does not contain the value" << std::endl;
    }
    return 0;
}
