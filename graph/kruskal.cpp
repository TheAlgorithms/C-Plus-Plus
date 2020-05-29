#include <iostream>
//#include <boost/multiprecision/cpp_int.hpp>
//using namespace boost::multiprecision;
const int mx = 1e6 + 5;
const long int inf = 2e9;
typedef long long ll;
#define rep(i, n) for (i = 0; i < n; i++)
#define repp(i, a, b) for (i = a; i <= b; i++)
#define pii pair<int, int>
#define vpii vector<pii>
#define vi vector<int>
#define vll vector<ll>
#define r(x) scanf("%d", &x)
#define rs(s) scanf("%s", s)
#define gc getchar_unlocked
#define pc putchar_unlocked
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define endl "\n"
#define fast                          \
	ios_base::sync_with_stdio(false); \
	cin.tie(NULL);                    \
	cout.tie(NULL);
using namespace std;
void in(int &x)
{
	register int c = gc();
	x = 0;
	int neg = 0;
	for (; ((c < 48 || c > 57) && c != '-'); c = gc())
		;
	if (c == '-')
	{
		neg = 1;
		c = gc();
	}
	for (; c > 47 && c < 58; c = gc())
	{
		x = (x << 1) + (x << 3) + c - 48;
	}
	if (neg)
		x = -x;
}
void out(int n)
{
	int N = n, rev, count = 0;
	rev = N;
	if (N == 0)
	{
		pc('0');
		return;
	}
	while ((rev % 10) == 0)
	{
		count++;
		rev /= 10;
	}
	rev = 0;
	while (N != 0)
	{
		rev = (rev << 3) + (rev << 1) + N % 10;
		N /= 10;
	}
	while (rev != 0)
	{
		pc(rev % 10 + '0');
		rev /= 10;
	}
	while (count--)
		pc('0');
}
ll parent[mx], arr[mx], node, edge;
vector<pair<ll, pair<ll, ll>>> v;
void initial()
{
	int i;
	rep(i, node + edge)
		parent[i] = i;
}
int root(int i)
{
	while (parent[i] != i)
	{
		parent[i] = parent[parent[i]];
		i = parent[i];
	}
	return i;
}
void join(int x, int y)
{
	int root_x = root(x); //Disjoint set union by rank
	int root_y = root(y);
	parent[root_x] = root_y;
}
ll kruskal()
{
	ll mincost = 0, i, x, y;
	rep(i, edge)
	{
		x = v[i].second.first;
		y = v[i].second.second;
		if (root(x) != root(y))
		{
			mincost += v[i].first;
			join(x, y);
		}
	}
	return mincost;
}
int main()
{
	fast;
	while (1)
	{
		int i, j, from, to, cost, totalcost = 0;
		cin >> node >> edge; //Enter the nodes and edges
		if (node == 0 && edge == 0)
			break; //Enter 0 0 to break out
		initial(); //Initialise the parent array
		rep(i, edge)
		{
			cin >> from >> to >> cost;
			v.pb(mp(cost, mp(from, to)));
			totalcost += cost;
		}
		sort(v.begin(), v.end());
		// rep(i,v.size())
		// 	cout<<v[i].first<<"  ";
		cout << kruskal() << endl;
		v.clear();
	}
	return 0;
}
