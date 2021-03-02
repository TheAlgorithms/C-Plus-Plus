
#include <iostream>
using namespace std;
typedef long long ll;


int trailing_zeros(ll n)
{

    ll ans= 0;

    // Keep dividing n by powers of 5 and update count
    for (ll i =5;n/i >= 1;i*=5)
        ans+= n / i;
     return ans;
}

//main function
int main()
{
    ll n;
    cin>>n;
    cout << "Count of trailing 0s in " << n
         << "! is " << trailing_zeros(n);
    return 0;
}
