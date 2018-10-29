//Implementation of comb sort in C++.
#include <iostream>
using std::cout; using std::endl; using std::cin;
#include <vector>
using std::vector;

void combSort (vector<int> &vec)	{

	int gap = vec.size(), shrinkfactor = 13, placeholder;
	bool sorted = false;

	while (sorted == false)	{
		
		gap = ((gap * 10) / shrinkfactor) / 10;

		if (gap > 1)
			sorted = false;
		else	{
			gap = 1;
			sorted = true;
		}

		for (unsigned int i = 0; i + gap < vec.size(); i++)	{
			if (vec[i] > vec[i+gap])	{
				placeholder = vec[i];
				vec[i] = vec[i+gap];
				vec[i+gap] = placeholder;

				sorted = false;
			}
		}
	}
}

int main()	{

	vector<int> vec;
	int x;

	cout << "Number of elements: ";
	cin >> x;
	cout << endl;
	vec.resize(x);

	cout << "Enter " << x << " integer elements individually below." 
		<< endl;
	
	for (int y = 0; y < x; y++)
		cin >> vec[y];

	cout << endl;
		
	cout << "Original vector: {";
	for (unsigned int z = 0; z < vec.size(); z++)
		cout << vec[z] << ", ";
	cout << "\b\b}" << endl;

	combSort(vec);

	cout << "Sorted vector: {";
	for (unsigned int z = 0; z < vec.size(); z++)
		cout << vec[z] << ", ";
	cout << "\b\b}" << endl;
}
