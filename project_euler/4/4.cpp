#include<iostream>

using namespace std;

/*
bool rev(int *arr, int n)
{
    int i;
    bool flag;
    for(i=0;i<n/2;i++)
    {
        if(arr[i]==arr[n-1-i])
            flag=true;
        else
            flag=false;
    }
    return flag;
}

*/

int rev(int i, int digits)
{
    int r = 0;
    int n = digits;
    while(n>0)
    {
        r = 10*r + i%10;
        i /= 10;
        --n;
    }
    return r;
}
    

bool isPalin(int num)
{
    bool flag = false;
    int n = rev(num, 6);
    if(num == n)
        flag = true;
    return flag;
}


/*
void multiplyArr(int *a, int *b) //(, int n, int m)
{
    int n=6;    
    int *arr = new int[n];
    int ans = a*b;
    for(int i=0;i<n;i++)
    {
        arr[i] = ans/pow(10,(n-i-1));
    }
    for(i=0;i<n;i++)
    {
        cout<<a[i];
    }
}
*/

void highPalin()
{
    int hPalin = 0;
    int a,b,diff;
    a=999;
    while(a>=100)
    {
        if(a%11 == 0)
        {
            b=999;
            diff = 1;
        }
        else
        {
            b=990;
            diff=11;
        }
        while(b>=a)
        {
            if(a*b<=hPalin)
                break;
            else if(isPalin(a*b))
                hPalin=a*b;
            b-=diff;        
        }
        a-=1;
    }
    cout<<hPalin;
}

int main()
{
    highPalin();
    return 0;
}
