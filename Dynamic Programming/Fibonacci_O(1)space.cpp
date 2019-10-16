#include<bits/stdc++.h>
using namespace std;

long int fib(long int n)
{
    if(n==1 || n==2)
        return 1;
    long int count = 2;
    long int a = 1;
    long int b = 1;
    long int c;
    while(count != n)
    {
        c = a+b;
        a = b;
        b = c;
        count += 1;
    }
    return c;
}

int main()
{
    long int n;
    cin>>n;
    cout<<fib(n);
}
