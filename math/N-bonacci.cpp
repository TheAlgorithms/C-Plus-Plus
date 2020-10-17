
/**
 * @file N-bonacci.cpp
 * @brief Implementation of N-bonacci Series 
 * @author [Neha Hasija](https://github.com/neha-hasija17)
 */
#include <iostream>
#include <vector>
/*
*In general, in N-bonacci sequence, 
*we generate sum of preceding N numbers from the next term. 
*For example, a 3-bonacci sequence is the following:
*0, 0, 1, 1, 2, 4, 7, 13, 24, 44, 81
*In this code we take N and M as input where M is the number of terms
*to be printed of the N-bonacci series
*/
void N_bonacci(int n,int m){
	 /**
             * This function finds N-bonacci series for
             * @param n value and @param m terms and prints the series
             */        
	std::vector<int> a(m,0); //we create an empty array of size m(number of terms to be printed)
	int i;
		a[n-1]=1;///we initialise the (n-1)th term as 1 which is the sum of preceding N zeros
		a[n]=1; ///similarily the sum of preceding N zeros and the (N+1)th 1 is also 1
		for(i=n+1;i<m;i++){
			/*this is an optimized solution which works in O(M) time and takes O(M) extra space
			*here we use the concept of sliding window
			*the current term can be computed using the given formula
			*/
			a[i]=2*a[i-1] - a[i-1-n];
		}
		/// Now we one by one print the terms 
	        /// of the N-Bonacci series
		std::cout<<"The "<<n<<"-Bonacci series till "<<m<<" terms is"<<std::endl;
			for(i=0;i<m;i++){
			std::cout<<a[i]<<" ";
		}
		std::cout<<std::endl;
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
	int t,n,i,m;
	std::cout<<"Enter number of testcases :";
	std::cin>>t; 
	while(t--){
		std::cout<<"Enter the values of N and M : ";
		std::cin>>n>>m;
		N_bonacci(n,m);
	
	}
	return 0;
}
