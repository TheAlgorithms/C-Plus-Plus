/*
Explanation:
https://www.hackerrank.com/contests/mock-icpc-august/challenges/boston-numbers
*/


#include <iostream>
#include<cmath>
using namespace std;
int main() {
   long n,temp,temp2,sum1=0,i=0;
   cin>>n;
   int a[100]={0};
   temp=n;
   while(temp>0){
       sum1+=temp%10;
       temp/=10;
   }
   while (n % 2 == 0)
    {
        a[i]=2;
        n = n/2;
        i++;
    }
    for (long j = 3; j <= sqrt(n); j+= 2)
    {
        while (n % j == 0)
        {
            a[i]=j;
            n = n/j;
            i++;
        }
    }
     if (n > 2){
          a[i]=n;
     }  
    long sum2=0;
    for(long j=0;j<=i;j++){
        if(a[j]<10){
            sum2+=a[j];
        }
        else{
            temp2=a[j];
            while(temp2>0){
                long rem=temp2%10;
                sum2+=rem;
                temp2/=10;
            }
        }
    }
    if(sum1==sum2){
        cout<<1;
    }
    else{
    cout<<0;
    }
       
}
