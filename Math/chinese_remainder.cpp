/*
Given two arrays num[0...k-1] and rem[0...k-1]. Here, k denotes number of equations.
In num[0..k-1], every pair is coprime (gcd for every pair is 1).
We need to find minimum positive number x such that: 

     x % num[0]    =  rem[0], 
     x % num[1]    =  rem[1], 
     .......................
     x % num[k-1]  =  rem[k-1] 
*/

#include <iostream>

using namespace std;

#define boost ios_base::sync_with_stdio(false), cin.tie(NULL)
#define ll long long
#define mod 1000000007
#define endl "\n"

/* 
Calculating inverse p^-1 mod q using extended Euclid's algorithm.
*/
ll inverse(ll p, ll q) {
    ll r1 = q, r2 = p, quo, r, t1 = 0, t2 = 1, t;
    while(r1 > 1 && r2 != 0) {
        quo = r1 / r2;
        r = r1 - quo * r2;
        t = t1 - quo * t2;
        r1 = r2;
        r2 = r;
        t1 = t2;
        t2 = t;
    } 
    if(r1 != 1 || r2 == 0) {
        cout<< "Inverse doesn't exist" << endl;
        exit(0);
    }
    if(t1 < 0)
    t1 += q;
	cout<<r1<<" "<<r2<<endl;
    return t1;
}

/*
Function to find minimum x satisfying all equations
*/
ll find_Minimum_X(ll num[], ll rem[], int k) {
    ll product = 1;
    for( int i = 0; i < k; i++) {
        product *= num[i];
    }
    
    ll result = 0;
    for(int i=0; i < k; i++) {
        ll quo = product / num[i];
        result += (rem[i] * inverse(quo, num[i]) * quo);
    }

    return result % product;
}

int main() 
{
    boost;  // for fast i/p and o/p
    int i, j, l, m;
    int k;  // number of equations
    cin >> k;
    ll num[k+1], rem[k+1];
    for(i = 0; i < k; i++) {
        cin >> num[i];
    }
    for(i = 0; i < k; i++) {
        cin >> rem[i];
    }
    
    ll answer = find_Minimum_X(num, rem, k);
    cout<<"Minimum possible X satisfying all "<< k <<" equations is: "<<answer<<endl;
    return 0;
}
