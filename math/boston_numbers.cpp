#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

vector<int> getAllPrimes(int n)
{
    vector<int> v;
    while(n%2==0)
    {
        v.push_back(2);
        n/=2;
    }

    for (int i = 3; i < sqrt(n)+1; i+=2)
    {
        while(n%i==0)
        {
            v.push_back(i);
            n/=i;
        }
    }

    if(n>2)
    {
        v.push_back(n);
    }

    return v;
    
}

int AddPrimes(vector<int> v)
{
    int sum = 0;
    for (int i = 0; i < v.size(); i++)
    {
        while(v[i])
        {
            sum+=v[i]%10;
            v[i]/=10;
        }
    }
    return sum;
    
}

int AddDigitsOfNumbers(int num)
{
    int sum1=0;
    while(num)
    {
        sum1+=num%10;
        num/=10;
    }

    return sum1;
}


bool IsBostonNumber(int num)
{
    vector<int> v = getAllPrimes(num);
    int result1 = AddPrimes(v);
    int result2 = AddDigitsOfNumbers(num);

    return result1==result2;

}

int main()
{
    int n;
    cin>>n;
    cout<<IsBostonNumber(n)<<endl;
    return 0;
}