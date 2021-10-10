/*
*@file
* \brief Program to check if a number is an [Boston 
* Number](https://www.hackerrank.com/contests/mock-icpc-august/challenges/boston-numbers)
* \details 
*   A Boston number is a composite number, 
*    the sum of whose digits is the sum of the 
*   digits of its prime factors obtained as a 
*   result of prime factorization (excluding 1 ).
*    The first few such numbers are 4,22 ,27 
*    ,58 ,85 ,94 and 121 . For example, 378 = 
*    2 × 3 × 3 × 3 × 7 is a Boston number since 
*   3 + 7 + 8 = 2 + 3 + 3 + 3 + 7.

* @author rahul-mishra-oops (https://github.com/rahul-mishra-oops)



*/






#include<iostream>
#include<vector>
#include<cmath>

using namespace std;
// Function to find all the prime facrors of the number
// @param n number
// @return vector with all prime factors
vector<int> getAllPrimes(int n)
{
    vector<int> v;
    while(n%2==0)
    {
        v.push_back(2);
        n/=2;
    }

    for (int i = 3; i < sqrt(n)+1; i+=2)
    {
        while(n%i==0)
        {
            v.push_back(i);
            n/=i;
        }
    }

    if(n>2)
    {
        v.push_back(n);
    }

    return v;
    
}

//Function to add all the digits of prime factors
// @param vector v
// @return the sum of all digits
int AddPrimes(vector<int> v)
{
    int sum = 0;
    for (int i = 0; i < v.size(); i++)
    {
        while(v[i])
        {
            sum+=v[i]%10;
            v[i]/=10;
        }
    }
    return sum;
    
}

//Function to calculate the digits of number
// @param number num
// @return sum of all digits of number
int AddDigitsOfNumbers(int num)
{
    int sum1=0;
    while(num)
    {
        sum1+=num%10;
        num/=10;
    }

    return sum1;
}

//Function to check if the number is boston Number or not
//@param number num
//@return true or false
bool IsBostonNumber(int num)
{
    vector<int> v = getAllPrimes(num);
    int result1 = AddPrimes(v);
    int result2 = AddDigitsOfNumbers(num);

    return result1==result2;

}

//main function

int main()
{
    int n;
    cin>>n;
    cout<<IsBostonNumber(n)<<endl;
    return 0;
}