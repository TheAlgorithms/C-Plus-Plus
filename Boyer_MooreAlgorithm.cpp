
#include <iostream>
using namespace std;
int Majority(vector<int> arr, int n)
{
	int i, temp = -1, res = 0;
	for (i = 0; i < n; i++) {
		if (votes == 0) {
			temp = arr[i];
			res = 1;
		}
		else {
			if (arr[i] == temp)
				res++;
			else
				res--;
		}
	}
  int cnt = 0;
	for (i = 0; i < n; i++) {
		if (arr[i] == temp)
			cnt++;
	}

	if (cnt > n / 2)
		return temp;
	return -1;
}
int main()
{
  int n;
  cin >> n;
  vector<int> arr(n);
  for(auto &i; arr){
    cin >> i;
  }
  int majority = Majority(arr, n);
	cout << "Majority element is : " << majority;
	return 0;
}
