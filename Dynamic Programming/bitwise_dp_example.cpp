#include <iostream>
#include <vector>

#define mod 1000000007
#define mx 1000005

#define rep(i,n) for(i=0;i<n;i++)
#define invrep(i,n) for (i = n-1; i >=0 ; --i)

#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef long long int ll;
typedef pair<ll,ll> pl;
ll N,n;

std::vector<pl> V;
	ll A[mx];
	ll DP[1<<21]={0};
	ll pre[21][mx]={{0}};

ll fun(int a,int b){
	if (DP[b]!=0)
	{
		return DP[b];
	}
	if (a==n)
	{
		//cout<<"hi";
		return 0;
	}
	ll an,ans,i,j,k,x,y,z;
	an=mx;
	for (i = 0; i < N; ++i)
	{
		if(((b>>i)&1)!=1){
			ans=pre[V[i].f][a+V[i].s-1]-pre[V[i].f][a];
			if (V[i].f==A[a])
			{
				ans++;
			}
			ans=V[i].s-ans;
			ans+=fun(a+V[i].s,b|(1<<i));
			
			if (an>ans)
			{
				an=ans;
			}
		}
	}
	return DP[b]=an;
}


int main(int argc, char const *argv[])
{
	ll a,b,c,i,j,k,f,r,t,m,x,y,z,p,q;
	cin>>n>>m;
	ll B[21]={0};
	
		f=0;
		r=0;
		for (int i = 0; i < n; ++i)
		{
			cin>>A[i];
			B[A[i]]++;
		}
		rep(i,21){
			if(B[i]!=0)
			{
				V.pb(mp(i,B[i]));
				N++;
			}
		}
		pre[A[0]][0]++;
		for(i=1;i<n;i++){
			rep(j,21){
				pre[j][i]=pre[j][i-1];
			}
			pre[A[i]][i]++;
		}
		cout<<fun(0,0);


	return 0;
}
