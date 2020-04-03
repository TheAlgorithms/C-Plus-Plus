#include<iostream>
#include<cmath>

using namespace std;

long int evenFib(int n)
{
    if (n < 1)
       return n;
    if (n == 1) 
       return 2;
 
    // calculation of fn= 4*(fn-1) + fn-2, I will probably create a Readme of How this formula is derived
    return ((4*evenFib(n-1)) + evenFib(n-2));  
}

void sumEvenFib(long n)
{
    long sum=0,fib=0;
    int i=1;
    bool flag=true;
    while(flag)
    {
        fib = evenFib(i);
        i++;
        if(fib<=n)
        {
            flag = true;
            sum += fib;     // be carefull here!! I would recommend you should try to optimise this for best performance
        }
        else
        {
            flag = false;
        }
    }
    cout<<sum<<endl;
}


int main()
{
    const int num = 4000000;
    sumEvenFib(num);   // this program takes less 0.004 s to execute in a laptop with linux os with 4 gb ram and i3 64 bit processor
    return 0;
}
