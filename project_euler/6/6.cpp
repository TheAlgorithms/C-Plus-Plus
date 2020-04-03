#include<iostream>

// One advice: Read the questions properly :P
// I am saying this from experience 

using namespace std;

long sum_n2(int n)
{
    return (((n)*(n+1)*((2*n)+1))/6);
}

long sum_n(int n)
{
    return (((n)*(n+1))/2);
}

long square_sum(long n) 
{
    return n*n;
}

int main()
{
    const int num = 100;
    long ans = square_sum(sum_n(num)) - sum_n2(num);
    cout<<ans<<endl;
    return 0;
}
