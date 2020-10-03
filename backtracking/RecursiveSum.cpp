/* 
Title - Recusive Sum
Description- A Program to recursively calculate sum of N natural numbers.
*/

#include<bits/stdc++.h>
using namespace std;

// A recursive function to calculate the sum of N natural numbers
int recursiveSum(int num)
{
    if(num == 0) 
    return 0;   
    return (recursiveSum(num - 1) + num); 
}

int main()   
{
    int num;
    cout<<"\n Enter a number N to find sum of first N natural numbers: ";
    cin>>num;    
    cout<<"\n Sum of first "<<num<<" natural numbers is = "<<recursiveSum(num); 
    return 0;
}

/*
Time complexity - O(n)
Sample Input - 5
Sample Output - 15
*/
