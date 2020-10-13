/**
 * @file 
 * @brief  Implementation of [Bubble sort](https://en.wikipedia.org/wiki/Bubble_sort) recursive algorithm.
 * @details 
 * Bubble sort, sometimes referred to as sinking sort, is a simple sorting algorithm that repeatedly steps through the list, 
 * compares  adjacent elements and swaps them if they are in the wrong order. The pass through the list is repeated until the list is   
 * sorted. The algorithm, which is a comparison sort, is named for the way smaller or larger elements "bubble" to the top of the list.
 * 
 * 
 * ### Bubble sort
 * Bubble sort is a simple sorting algorithm. 
 * This sorting algorithm is comparison-based algorithm in which each pair of adjacent elements is compared and the elements are swapped if they are not in order. 
 * This algorithm is not suitable for large data sets as its average and worst case complexity are of Ο(n^2) where n is the number of items.
 * 
 * ### Recursive approach
 * Bubble sort compares adjacent pairs and swaps them if they are in the wrong order. 
 * In this type of bubble sort, we use the recursive function that calls itself.
 * Use of recursive (self-calling) function compares adjacent pairs and swaps them if they are in the wrong order until the array is in order.
 *
 * ### Concept
 * Recursive Bubble Sort has no performance/implementation advantages, but can be a good question to check one’s understanding of Bubble Sort and recursion.
 * If we take a closer look at Bubble Sort algorithm, we can notice that in first pass, we move largest element to end (Assuming sorting in increasing order). 
 * In second pass, we move second largest element to second last position and so on.
 * 
 * 
 * ### Algorithm
 * 1) Base Case: If array size is 1, return.
 * 2) Do One Pass of normal Bubble Sort. This pass fixes last element of current subarray.
 * 3) Recur for all elements except last of current subarray.
 * 
 * 
 *
 * @author [Krishna Pal Deora](https://github.com/Krishnapal4050)
 * 
 */


#include<iostream>
#include <array> 

void recBubble(std::array<int,10> arr, int n){
   if (n == 1){
      return;
   }
   for (int i=0; i<n-1; i++) //for each pass p
   { 
      if (arr[i] > arr[i+1]) //if the current element is greater than next one
      { 
          std::swap(arr[i], arr[i+1]); //swap elements
      } 
   }

   recBubble(arr, n-1);
}


int main() 
{
   std::array<int,10> data = {54, 74, 98, 154, 98, 32, 20, 13, 35, 40};
   int n = sizeof(data)/sizeof(data[0]);
   std::cout << "Sorted Sequence ";
   recBubble(data, n);
   for(int i = 0; i <n;i++)
   {
      std::cout << data[i] << " ";
   }
   
   return 0;
}
