#include<iostream>
using namespace std;

int main()
{
    int n;
    cout<<"Enter number = ";
    cin>>n;
    int num=1;
    for(int i=1;i<n;i++)
    {
        num*=i;
    }
    cout<<"Factorial of number is = ";
    cout<<num<<endl;

    return 0;
}
