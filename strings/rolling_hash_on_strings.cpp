#include <iostream>
#include <vector>
using namespace std;

/*
    * How to use: consider 2 strings "asian" and "aside"
    * create a vector<pair<long long,long long>> to store hash for (each) string
    * pass it to init(hashVector , stringToBeHashed) 
    * substring [1,3] of "asian" == substring [1,3] of "aside" [1-indexed]
    * confirm by passing computeRange(1,3,hashOfFirstString) == computeRange(1,3,hashOfSecondString)
*/
const int p1 = 31;
const int p2 = 37;
const int MOD= 1e9 +7;
const int arrayLength = 2e5+1;
long long pow_p1[arrayLength],pow_p2[arrayLength];
static int x = [](){
    pow_p1[0]=pow_p2[0]=1;
    for(int i=1;i<=arrayLength-1;i++)
    {
        pow_p1[i]=(p1*pow_p1[i-1])%MOD;
        pow_p2[i]=(p2*pow_p2[i-1])%MOD;
    }
    return 0;
}();
void init(vector<pair<long long,long long>> &hash,const string &s)
{
    int l=s.length();
    hash.resize(1+l,make_pair(0ll,0ll));

    for(int i=1;i<=l;i++)
    {
        int charConv=(s[i-1]-'a'+1);
        long long h1=(charConv*pow_p1[i-1])%MOD;
        hash[i].first=(hash[i-1].first + h1)%MOD;

        long long h2=(charConv*pow_p2[i-1])%MOD;
        hash[i].second=(hash[i-1].second + h2)%MOD;
    }
}
pair<long long,long long> computeRange(int l,int h,vector<pair<long long,long long>> &hash)
{
    int n=hash.size()-1;
    long long h1=(hash[h].first+MOD -hash[l-1].first)%MOD;
    h1=(h1*pow_p1[n-l])%MOD;

    long long h2=(hash[h].second +MOD -hash[l-1].second)%MOD;
    h2=(h2*pow_p2[n-l])%MOD;

    return make_pair(h1,h2);
}


int main()
{
    string s1 = "asian",s2="aside";
    vector<pair<long long,long long>> hashOfFirstString,hashOfSecondString;
    init(hashOfFirstString,s1);
    init(hashOfSecondString,s2);
    
    // is [1,3] of asian same as [1,3] of "aside"?
    if(computeRange(1,3,hashOfFirstString) == computeRange(1,3,hashOfSecondString))
        cout<<"Yes they are same";
    else
        cout<<"No they are different";
    
    return 0;
}
