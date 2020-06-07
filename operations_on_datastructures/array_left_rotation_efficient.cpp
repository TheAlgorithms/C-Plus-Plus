#include<iostream>

int main()
{
        int n, d;
	::std::cout << "Enter size of array=\t";
	::std::cin >> n;
	::std::cout << "Enter Number of indeces u want to rotate the array to left=\t";
        ::std::cin >> d;
	int a[n];
	::std::cout << "Enter  elements of array=\t";
	for (int i = 0; i < n; i++) {
		::std::cin >> a[i];
	}
    int arr[d];
    for(int i = 0; i < d; i++) {
        arr[i] = a[i];
    }
    int j=0;
    for(int i = d; i< n; i++) {
    a[j] = a[i];
    j++;
    }
    j=0;
    for(int i = n-d; i < n; i++) {
    	a[i] = arr[j];
        j++;
    }
	cout << "Your rotated array is=\t";
	for (int j = 0; j < n; j++) {
	    ::std::cout << a[j] << " ";
	}
	return 0;
}
