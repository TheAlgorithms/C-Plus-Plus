// Given two arrays, check if one array is stack permutation of other

#include<bits/stdc++.h>
using namespace std;

bool checkStackPermutation(int ip[], int op[], int n)
{
	queue<int> input;
	for (int i=0;i<n;i++)
		input.push(ip[i]);

	queue<int> output;
	for (int i=0;i<n;i++)
		output.push(op[i]);

	stack <int> tempStack;
	while (!input.empty())
	{
		int ele = input.front();
		input.pop();
		if (ele == output.front())
		{
			output.pop();
			while (!tempStack.empty())
			{
				if (tempStack.top() == output.front())
				{
					tempStack.pop();
					output.pop();
				}
				else
					break;
			}
		}
		else
			tempStack.push(ele);
	}
	return (input.empty()&&tempStack.empty());
}

int main()
{
	int input[] = {1, 2, 3};
	int output[] = {2, 1, 3};

	int n = 3;

	if (checkStackPermutation(input, output, n))
		cout << "Yes";
	else
		cout << "Not Possible";
	return 0;
}
