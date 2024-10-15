/*
The Moore Voting Algorithm is an efficient way to find the majority element in an array. A majority element is defined as an element that appears more than n/2 times in the array.
This algorithm is important in scenarios where the majority element needs to be identified efficiently, such as in voting systems or stream processing applications

to find majority element we have few approaches to solve this problem 
1.) using nested for loops :- for every element count its occurence by traversing the entire array
    Time and space Complexity :- O(n*n) , O(1)

2.) using Unordered_map :- store occurences of each element as key with their frequency count as value and check element value i.e its count > n/2 inside map;
    Time and space Complexity :- O(n) , O(n) 

3.) Applying Moore Voting Algorithm :-  finding majority element in linear time by mainting vote count.
    Time and space Complexity :- O(n) , O(1) 

*/

// Implementation
#include "iostream"
int majorityelementement(int nums[],int n) {

    int element; // to store the value of the majority element
    int count = 0; // maintain the count which helps to determine if at the end count is not zero then we have an majority element stored in element variable

    for (int i = 0; i < n; i++) {
        if (count == 0) { // if element does not contain any value or count is 0
            element = nums[i];
            count++;
        } else if (nums[i] == element) {  // if nums[i] equals to element then increment the count value
            count++;
        }else {
            count--; // if nums[i] not equals to element then decrement the count value
        }
    }

    // verification by making a traversing the array , checking each element with our elment value maintaing its frequency and at last check the count1 > n/2
    int count1 = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] == element) { // if nums[i] equals to element then increment the count1 value
            count1++;
        }
    }
    if (count1 > n / 2) { // checking the element frequency represented by count1 is an majority element
        return element;
    }

    // if there is no majority element 
    return -1;
}

int main(){
    int n = 9;
    int arr[n] = {3, 3, 4, 2, 4, 4, 2, 4, 4};
    int majority_element = majorityelementement(arr,n);
    if(majority_element!=-1){
        std::cout<<"Majority Element: "<<majority_element<<std::endl;
        // Majority Element: 4
    }else{
        std::cout<<"No Majority Element Found "<<std::endl;
    }
}