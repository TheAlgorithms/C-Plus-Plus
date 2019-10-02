#include <iostream>
using namespace std;
int binary_search(int *a, int s, int e, int key)  //'s' is left most element and 'e' is right most element of the array to be searched
{
    int mid=(s+e)/2;
    if(s>e)
    {
        return -1;
    }
    if(key==a[mid])
    {
        return mid;
    }
    if(key>a[mid])
    {
         binary_search(a,mid+1,e,key);
    }
    else if(key<a[mid])
    {
         binary_search(a,s,mid-1,key);
    }
}
int main(int argc, char const *argv[])
{
	int n, key;
	cout << "Enter size of array: ";
	cin >> n;
	cout << "Enter array elements: ";
	int a[n];
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
	}
	cout << "Enter search key: ";
	cin >> key;
	int res = binary_search(a, 0, n - 1, key);
	if (res != -1)
		cout << key << " found at index " << res << endl;
	else
		cout << key << " not found" << endl;
	return 0;
}
