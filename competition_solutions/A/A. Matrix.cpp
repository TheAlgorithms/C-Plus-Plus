#include<bits/stdc++.h>
using namespace std;
                 //Welcome To Hridoy's Code
#define   ll                  long long
#define   ull                 unsigned long long
#define   pb                  push_back
#define   em                  emplace_back
#define   ff                  first
#define   ss                  second
#define   endl                "\n"
#define   all(v)              (v.begin(), v.end())
#define   rall(v)             (v.rbegin(), v.rend())
#define   pi                  acos(-1.0)
#define   LCM(LCM_X,LCM_Y)    (LCM_X/__gcd(LCM_X,LCM_Y))*LCM_Y
#define   FastRead   ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
const int MOD = (int)1e9+7;
const int MAX = 1e6;
int main(){
	FastRead
	int n;
	while (scanf("%d", &n) == 1){
		int sum[4001] = { 0 };
		int Q[36001] = { 0 };
		int total = 0;
		char S[4001];
		int len;
		long long int ans = 0;
		scanf("%s", S);
		len = strlen(S);
		for (int i = 1; i <= len; i++){
			sum[i] = sum[i - 1] + S[i - 1] - '0';
			for (int j = 0; j < i; j++)
				Q[sum[i] - sum[j]]++;
		}
		for (int i = 0; i <= 36000; i++)
			total += Q[i];
		for (int i = 1; i <= len; i++){
			for (int j = i; j <= len; j++){
				if (sum[j] - sum[i - 1] > 0 && n % (sum[j] - sum[i - 1]) == 0){
					if (n / (sum[j] - sum[i - 1]) <= 36000)
						ans += Q[n / (sum[j] - sum[i - 1])];
				}
				else if (sum[j] - sum[i - 1] == 0 && n == 0){
					ans += total;
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
