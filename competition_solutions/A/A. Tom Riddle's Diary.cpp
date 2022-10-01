#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
    ll n;
    map<ll,ll>mp;
    map<ll,ll>kp;
    cin>>n;
    ll cnet=1;
    while(n--)
    {
        ll id,sub;
        bool ok=false,bk=false;
        cin>>id>>sub;
        while(sub--)
        {
            ll r,k;
            cin>>r>>k;
            kp[r]++;
            mp[k]++;
            if(mp[k]>1)ok=true;
            if(kp[r]>1)bk=true;
        }
        if(ok==false && bk==false)
        {
            cout<<"Scenario #"<<cnet<<": "<<"possible\n";
        }
        else cout<<"Scenario #"<<cnet<<": " <<"impossible\n";

        cnet++;
    }
    return 0;
}
