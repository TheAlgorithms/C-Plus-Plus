/*Gifts Fixing
You have n gifts and you want to give all of them to children. Of course, you don't want to offend anyone, so all gifts should be equal between each other. The i-th gift consists of ai candies and bi oranges.
During one move, you can choose some gift 1≤i≤n and do one of the following operations:
eat exactly one candy from this gift (decrease ai by one);
eat exactly one orange from this gift (decrease bi by one);
eat exactly one candy and exactly one orange from this gift (decrease both ai and bi by one).
Of course, you can not eat a candy or orange if it's not present in the gift (so neither ai nor bi can become less than zero).
As said above, all gifts should be equal. This means that after some sequence of moves the following two conditions should be satisfied: a1=a2=⋯=an and b1=b2=⋯=bn (and ai equals bi is not necessary).
Your task is to find the minimum number of moves required to equalize all the given gifts.
You have to answer t independent test cases.

Input
The first line of the input contains one integer t (1≤t≤1000) — the number of test cases. Then t test cases follow.

The first line of the test case contains one integer n (1≤n≤50) — the number of gifts. The second line of the test case contains n integers a1,a2,…,an (1≤ai≤109), where ai is the number of candies in the i-th gift. The third line of the test case contains n integers b1,b2,…,bn (1≤bi≤109), where bi is the number of oranges in the i-th gift.
Output
For each test case, print one integer: the minimum number of moves required to equalize all the given gifts.

Sample Test Cases:
Test Case -1:
Input:
3
3
3 5 6 //ai
3 2 3 //bi
5
1 2 3 4 5
5 4 3 2 1
3
1 1 1
2 2 2

Output:
6
16 
0

Test Case-2:
Input:
2
6
1 1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1 1 1 1
3
10 12 8
7 5 4

Output:
4999999995
7
*/

#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int a[55], b[55], n;
		cin >> n;
		int mina = INT_MAX, minb = INT_MAX; //we intialize the value of mina with max possible value for A and minb as max possible value for B
		long long ans = 0;
		for (int i = 1; i <= n; i++) //it find the minimum value from 1st array
		{
			cin >> a[i];
			mina = min(mina, a[i]); 
		}
		for (int i = 1; i <= n; i++) //it find the minimum value from 2nd array
		{
			cin >> b[i];
			minb = min(minb, b[i]);
		}
		for (int i = 1; i <= n; i++) //for gift 1 we need to check max operation we need to do. we will subtract value of first element of both the gift with min element and the add the maximum out of it into answer, same goes for all the other gifts. and at the end we will output the sum of all min possible operations
		{
			ans += 1ll * max(a[i] - mina, b[i] - minb);
			//cout<<ans<<" "; //added this line for better understanding of logic, output of ans for 1st test case is 1 3 6   
		}
		cout << ans << endl;
	}
	return 0;
}