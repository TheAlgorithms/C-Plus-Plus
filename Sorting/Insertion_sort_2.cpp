//To sort the array while accepting values itself
#include <iostream>
using namespace std;

int main()
{
	int n;
	cout << "\nEnter the length of your array : ";
	cin >> n;
	int Array[n];
	cout << "\nEnter any " << n << " Numbers for Unsorted Array : ";

	//Input
	for (int i = 0; i < n; i++)
	{
		int temp;
    cin>>temp;
    //accepted new value
		int j = i - 1;
    //checking if the last element in the array is greater than the accepted number
    //if yes, keep moving the numbers one step to the right
		while (j >= 0 && temp < Array[j])
		{
			Array[j + 1] = Array[j];
			j--;
		}
    //add the accepted number to the desired location
		Array[j + 1] = temp;
	}

	//Output
	cout << "\nSorted Array : ";
	for (int i = 0; i < n; i++)
	{
		cout << Array[i] << "\t";
	}
	return 0;
}

/*
Test case:                                                                                                                                             
Enter the length of your array : 5                                                                                                            
                                                                                                                                              
Enter any 5 Numbers for Unsorted Array : 1                                                                                                    
2                                                                                                                                             
6                                                                                                                                             
3                                                                                                                                             
0

Sorted Array : 0        1       2       3       6                       
                                                 
*/
