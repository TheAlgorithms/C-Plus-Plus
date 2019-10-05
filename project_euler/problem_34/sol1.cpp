/* contributed by manav014*/

/*project_euler problem 34
Digit factorials

Question
145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the factorial of their digits.

Note: as 1! = 1 and 2! = 2 are not sums they are not included.*/

/*Explaination of the solution
The solution to this problem is very simple just like the one we solved in problem 30
for the solution we need to know the limit from where to start searching for numbers
from where we could start and to which number we should go on with the iteration
to get the starting value as it is mention in the question that 1! and 2! are not the sum of factorials.
so we are going to start from 11.
and as we could check that 9!=362880 and 7*9!=2540160 but 8*9!=2903040 which has 7 digits so can not from 8 digit number we will have 
to iterate till 2540160.
Now after that what we r going to do is to store the factorial of numbers 0 to 9 in an array as if we will not do so then we will have 
to calculate them everytime we want to get the sum.
now we will simply apply brute force solution for the problem

*/
#include <iostream>

using namespace std;
void solve()
{
    long long i,sum=0,copy;
    long long fact[]={1,1,2,6,24,120,720,5040,40320,362880};
    for(i=10;i<=2540160;i++)
    {
        copy=i;long long int sum1=0;
        while(copy>0)
        {
            sum1+=fact[copy%10];
            copy/=10;
        }
        
        if(sum1==i)
            sum+=sum1;
        
    }
    cout<<sum<<endl;
}

int main(){
  solve();
return 0;
}
