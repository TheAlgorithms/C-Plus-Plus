/**
 *
 * @file
 * A simple program to check if the given number if prime or not.
 *
 * @brief
 * Reduced all possibilities of a number which cannot be prime.
 */

#include <bits/stdc++.h> 
using namespace std;

/**
 * Function to check if the given number is prime or not.
 * @param num number to be checked.
 * @return if number is prime, it returns @ is a Prime, else it returns @ Not a Prime.
 * if a number is -ve or else 0 or 1 it returns @false
 */

/**
 * Main function
 */
int main(){

    long long int n;
    cin>>n;

    bool isPrime = 1;

    if (n <= 1) 
        return false;

     for(int i=2; i<n; i++){

         if(n%i==0){
             isPrime=0;
             break;
         }
     }

      if(isPrime==0){
          cout<<"Not a Prime"<<endl;
      }

       else{
           cout<<"is a Prime"<<endl;
       }
 return 0;
}

// edited by Malay Shah
