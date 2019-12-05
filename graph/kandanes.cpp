#include<iostream>

int LargestSumContigousSubarray(int* arr, int size) {//Finds the largest sum of a contigous subarray possible in a given integer array by Kadanes Algorithm
	int max_final = 0;//Final value of the max sum possible
	int  max_so_far = 0;//Max sum of the current subarray, we will iterate and find the largest possible value of this entity 
	for (int i = 0; i < size; i++){
		max_so_far += arr[i];
		if (max_so_far < 0)/*Checks if the sum is positive*/ {
			max_so_far = 0;
		}
		else if (max_final < max_so_far)/*Checks if the current sum is the largest*/ {
			max_final = max_so_far;/*sets the value of the largest sum computed so far*/
		}
	}
	return max_final;
}
int main(int argc, char const* argv[]) {
	int n;
	std::cout << "Enter array length" << std::endl;
	std::cin >> n;
	std::cout << "Enter array elements" << std::endl;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		std::cin >> arr[i];
	}
	std::cout << "Maximum Contigous Sum " << LargestSumContigousSubarray(arr, n) << std::endl;
