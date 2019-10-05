/* contributed by manav014*/

/*project_euler problem 30
Digit fifth powers
Question
Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

1634 = 14 + 64 + 34 + 44
8208 = 84 + 24 + 04 + 84
9474 = 94 + 44 + 74 + 44
As 1 = 14 is not a sum it is not included.

The sum of these numbers is 1634 + 8208 + 9474 = 19316.

Find the sum of all the numbers that can be written as the sum of fifth powers of their digits. */

/*Explaination of the solution
Just applied the simple brute force algorithm of the solution 
for the solution we need to know the limit from where to start searching for numbers
from where we could start and to which number we should go on with the iteration

so for that we will have to check that if all digits in the number are 9 so how many digits we would be getting in the answer
like 1*(9^5)=59049
and 4*(9^5)=236196
and 6*(9^5)=354294
but 7*(9^5)=413343
which has 6 digits only so it will not be possible to get the sum of 5th power of each digit, equal to the number itself as the number will have 7 digits.
so we will have to start from 11 upto 354294 and now just we have to do is to find the sum of 5th power of digits and check weather it is equal to the number
or not if it is  equal then add it to the sum else leave the same. 

*/
#include <iostream>
#include<cmath>
using namespace std;
void solve()
{
    long long int sum1=0;
for(long long int i=11;i<=354294;i++)
{
    long long int copy=i,sum=0;
    while(copy>0)
    {
        sum+=pow(copy%10,5);
        copy/=10;
    }
    if(sum==i)
    {
        sum1+=i;
    }
}
cout<<sum1<<endl;
}

int main(){
  solve();
return 0;
}
