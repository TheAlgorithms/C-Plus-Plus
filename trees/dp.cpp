#include<iostream>
using namespace std;

int fib(int n,int dp[])//Top Down(Recursion + Memorisation)
{
    if(n==2 or n==1 )
    {return n;}
    else if (n==0)
    {return 1;}
    if(dp[n]!=0)
    {
        return dp[n];
    }
    return dp[n] = fib(n-1,dp) + fib(n-2,dp) + fib(n-3,dp);
}

int fib2(int n)//(Iterative)
{
    int dp[n+1] = {0};
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;
    for(int i=3; i<=n; i++)
    dp[i] = dp[i-1] + dp[i-2] + dp[i-3];

    return dp[n];
}

int main()
{
cout<<"enter"<<endl;
int n,b,c;
cin>>n;
int a[n+1] = {0};
c = fib(n,a);
b = fib2(n);
cout<<c<<" "<<b;

 return 0;   
}