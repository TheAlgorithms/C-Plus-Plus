#include <bits/stdc++.h>
#define int long long int
#define f first
#define s second
#define pb push_back

using namespace std;
struct segmentTree
{
    vector<int> st;
    int n;
    void init(int size)
    {
        this->n=size;
        st.resize(4*n,0);
        
    }
    void build(int start,int end,int node ,vector<int> &v)
    {
        if(start==end)
        {
            st[node]=v[start];
            return ;

        }

        int mid=(start+end)/2;
        build(start,mid,2*node+1,v);
        build(mid+1,end,2*node+2,v);
        st[node]=st[2*node+1]+st[2*node+2];


    }
    void build(vector<int> &v)
    {
        build(0,v.size()-1,0,v);

    }
    int query(int start,int end,int l,int r,int node)
    {
        if(start>r || end<l)//non overlapping case
        return 0;
        if(start>=l && end<=r)//completey overlapping region
        return st[node];
//partial case
        int mid=(start+end)/2;
        int q1=query(start,mid,l,r,2*node+1);
        int  q2=query(mid+1,end,l,r,2*node+2);
        return q1+q2;


    }
    int query(int l,int r)
    {
        return query(0,n-1,l,r,0);//first four parameters are for checking overlapping,no-overlapping and partially overlapping conditions

    }
    void update(int start,int end ,int node,int index ,int value)
    {
        if(start==end)
        {
            st[node]=value;
            return ;

        }
        int mid=(start+end)/2;
        if(index<=mid)
        {
            update(start,mid,2*node+1,index,value);
        }
        else
        {
            update(mid+1,end,2*node+2,index,value);

        }
        st[node]=st[2*node +1]+st[2*node+2];
        return ;

    }
    void update(int x,int y )//at index 'x ' update the value to 'y'
    {
        update(0,n-1,0,x,y);//start from the root node

    }


};
struct fenwick
{
    int n;
    vector<int> fn;
    void init(int n)
    {
        this->n=n+1;
        fn.resize(this->n,0);

    }
    void add(int x,int y)
    {
        x++;
        while(x<n)
        {
            fn[x]+=y;
            x+=(x&(-x));

        }
    }
    int sum(int x)
    {
        x++;
        int ans=0;
        while(x)
        {
            ans+=fn[x];
            x-=(x&(-x));

        }
        return ans;

    }
    int sum(int l,int r)
    {
        return sum(r)-sum(l-1);

    }
};
const int N=100;
int v[N],w[N],W,n;
int memoise[N][100000];

int dp(int index,int weight)
{
    if(index>=n)
        return 0;
    int &ans=memoise[index][weight];
    if(ans!=-1)
        return ans;

     ans=dp(index+1,weight);
if(w[index]+weight<=W)
{
    ans=max(ans,v[index]+dp(index+1,weight+w[index]));
}
return ans;

}


int32_t main()
{
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    memset(memoise,-1,sizeof(memoise));

    cin>>n>>W;
    for(int i=0;i<n;i++)
    {
        cin>>w[i]>>v[i];

    }
    cout<<dp(0,0)<<endl;

 
   





}
