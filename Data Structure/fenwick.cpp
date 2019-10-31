#include<bits/stdc++.h>
using namespace std;

#define boost ios_base::sync_with_stdio(false), cin.tie(NULL)
#define rep(i,c,n) for(i=c;i<n;i++)
#define dw(t) while(--t>=0)
#define veci vector<int>
#define vecl vector<ll>
#define pb push_back
#define mp make_pair
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define ol(x) cout<<x<<endl
#define ll long long
#define mod 1000000007
#define ppl pair<ll,ll>
#define ppi pair<int,int>
#define endl "\n"
int BIT[100005] = {0};


int getSum(int index) {
    int sum = 0;
    index += 1;
    while(index > 0) {
        sum += BIT[index];
        index = index - (index & (-index));
    }

    return sum;
}

void updateBIT(int x, int n, int index) {
    index += 1;
    while(index <= n) {
        BIT[index] += x;
        index = index + (index & (-index));
    }
}

void constructBIT(int a[], int n) {
    int i,j;
    rep(i,0,n) updateBIT(a[i],n,i);
}

int main()
{
boost;
    int n,i,j;
    cin>>n;
    int a[n+1];
    rep(i,0,n) cin>>a[i];
    constructBIT(a,n);
    int q;
    cin>>q;
    int type,l,r;
    // type 0 for sum and 1 for updating
    dw(q) {
        cin >> type;
        if(type == 0)
        {
            cin>>l>>r;
            cout<< getSum(r) - getSum(l-1)<<endl;
        }
        else{
            cin>>l>>r;  // update a[l] = r;
            int now = a[l];
            int diff = r - now;
            updateBIT(diff, n, l);
        }
    }
return 0;
}

