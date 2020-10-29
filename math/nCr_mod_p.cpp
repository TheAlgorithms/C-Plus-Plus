/**
 * @file
 * @brief C++ program to find number of distinct ways of selecting r objects fom n distinct objects.
 *  SInce this number can be very large, we will calulate answer modulo p
 */
#include <iostream>
#include<vector>

using namespace std;

vector<long long> fac; //Store pre-computed factorials

/** function to find inverse modulo of given number */
long long inverse(long long i,long long m){
    if(i==1) return 1;
    return (m - ((m/i)*inverse(m%i,m))%m+m)%m;
}

long long nCr(long long n,long long r,long long p)
{
    if(r>n)
    return 0;
    else if(r==0||r==n)
    return 1;
    else
    {
        return(((fac[n]*inverse(fac[r],p))%p)*inverse(fac[n-r],p))%p;
    }
    
}
/** Main function */
int main() {
    int n,r,p;
    // p should be a prime number
    cin>>n>>r>>p;

    fac = vector<long long>(n+1);

    fac[0]=1;

    //Loop to pre-calculate i factorial for 0<=i<=n
    for(int i=1;i<=n;i++)
    {
        fac[i]=(fac[i-1]*i)%p;
    }

    long long answer = nCr(n,r,p);

    cout<<answer<<endl;

    return 0;
}