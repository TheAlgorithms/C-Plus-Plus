//Bubble Sort

#include<iostream>
#include<vector>
using namespace std;

int main()
{
	int n;
	short swap_check=0;
  	cout << "Enter the amount of numbers to sort: ";
	cin >> n;
	vector<int> numbers;
	cout << "Enter " << n << " numbers: ";
	int num;

  	//Input
	for(int i=0; i<n; i++)
	{
		cin >> num;
		numbers.push_back(num);
	}

	//Bubble Sorting
	for(int i=0; i<n; i++)
	{
		swap_check=0;
		for(int j=0; j<n-1-i; j++)
		{
			if(numbers[j]>numbers[j+1])
			{
				swap_check=1;
				swap(numbers[j], numbers[j+1]);
			}
		}
		if(swap_check == 0)
		{	
			break;
		}
	}

	//Output
	cout<<"\nSorted Array : ";
	for(int i=0; i<numbers.size(); i++)
	{
		if(i != numbers.size() -1)
		{
			cout << numbers[i] << ", ";
		}else
		{
			cout << numbers[i] << endl;
		}
	}
  return 0;
}
