/**
 * @file
 * @brief This program portrays a c++ implementation of the kadanes algorithm, 
 * which finds the maximum subarray sum (https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/)
 * @details
 *  The purpose of Kadanes algorithm is to dynamically traverse through every sum of contiguous subarrays and find the largest sum 
 *  of positive contiguous segments. First, the program goes through every positive continuous segment (possible subarrays). The variable 
 *  maxTemp keeps track of all the different sums of possible subarrays. If the subarray sum number goes below 0, it is set back to 0 because the 
 *  biggest sum is never 0. (https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/)
 *  
 * @author [Joseph Sulkes](https://github.com/jsulkes20)
 *  
 */
#include<climits>
#include<iostream>
#include<vector>
/**
 * @namespace operations_on_datastructures
 * @brief Operations on Data Structures
 */
namespace operations_on_datastructures {
  
/**
 * @brief kadanes algorithm (https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/)
 * @param original vector
 * @return largest possible subarray sum
 */

 int Kadanes(std::vector<int> arr)
{

  //  maxTemp is used to find every positive continuous segment 
  //  maxSum is the maximum subarray sum, which is returned
    int maxSum = INT_MIN; 
    int maxTemp = 0;
    int s = arr.size();
    for (int i = 0; i < s; i++)
    {
        maxTemp+= arr[i]; //add each element in the array each iteration to check every subarrays sum (maxTemp)
        if(maxSum < maxTemp) {
maxSum=maxTemp; //maxSum ends up as the biggest subarray sum
        }
          
        
        if(maxTemp<0) {
          maxTemp=0; //if the segment's sum is ever negative, set it to 0 because the biggest subarray sum will never be a negative number
        } 
         
        
}
 return maxSum;
}
} //namespace operations_on_datastructures
/**
 * @brief function to print the vector
 * @param vector to print
 * @return void
 */
void printVect(std::vector<int> v)
{
  int s= v.size();
  for (int i=0; i < s; i++) {
     std::cout << v[i] << " ";
    std::cout << std::endl;
  }
    
}
 
/**
 * @brief test function to test three different arrays and return *  the  maximum contiguous subarray sum. Each array has a       *  different size and different numbers  
 * @return void
 */
 static void test() {
   std::vector<int> vect{5,3,-2,4,-5,1,-4};
  std::vector<int> vect2{-2,-4,2,-1,6,-3,1};
  std::vector<int> vect3{5,1,-2,4,-5,3,-4,6};
    
    std::cout<< "Array example 1 is: \n"; 
    printVect(vect);
    int max = operations_on_datastructures::Kadanes(vect);
   std:: cout << "The maximum contiguous sum is " << max<<std::endl;
     
    std::cout<< "Array example 2 is: \n"; 
    printVect(vect2);
    int max2 = operations_on_datastructures::Kadanes(vect2);
    std::cout << "The maximum contiguous sum is "<< max2<<std::endl;
 
    std::cout<< "Array example 3 is: \n"; 
    printVect(vect3);
    int max3 = operations_on_datastructures::Kadanes(vect3);
    std::cout << "The maximum contiguous sum is " << max3<<std::endl;
 }

int main()
{
  test();
    return 0;
}

