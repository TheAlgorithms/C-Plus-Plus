  /* 
  Sorting array by frequency in decreasing order
  Program to Print the elements of an array in the decreasing frequency if 2 numbers have same frequency then print the one which came first. 

  Input:  arr[] = {2, 5, 2, 8, 5, 6, 8, 8}

    After sorting we get
    Element 2 2 5 5 6 8 8 8
    Index   0 2 1 4 5 3 6 7

    Now construct the 2D array as
    Index, Count
    0,      2
    1,      2
    5,      1
    3,      3

    Sort by count (consider indexes in case of tie)
    3, 3
    0, 2
    1, 2
    5, 1

    Print the elements using indexes in the above 2D array.
    Output: arr[] = {8, 8, 8, 2, 2, 5, 5, 6}

  Using a hashing mechanism, we can store the elements (also first index) and their counts in a hash. Finally, sort the hash elements according to their counts.
  Below is the implementation of above approach – 
  
  */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

// Compare function
bool fcompare(std::pair<int, std::pair<int, int> > p,
			std::pair<int, std::pair<int, int> > p1)
{
	if (p.second.second != p1.second.second)
		return (p.second.second > p1.second.second);
	else
		return (p.second.first < p1.second.first);
}
void sortByFrequency(int arr[], int n)
{
	std::unordered_map<int, std::pair<int, int> > hash; // hash map
	for (int i = 0; i < n; i++) {
		if (hash.find(arr[i]) != hash.end())
			hash[arr[i]].second++;
		else
			hash[arr[i]] = std::make_pair(i, 1);
	} // store the count of all the elements in the hashmap

	// Iterator to Traverse the Hashmap
	auto it = hash.begin();

	// Vector to store the Final Sortted order
	std::vector<std::pair<int, std::pair<int, int> > > b;
	for (it; it != hash.end(); ++it)
		b.push_back(std::make_pair(it->first, it->second));

	sort(b.begin(), b.end(), fcompare);

	// output
	for (int i = 0; i < b.size(); i++) {
		int count = b[i].second.second;
		while (count--)
			std::cout << b[i].first << " ";
	}
}

int main()
{
    int n;
   
    std::cout << "Enter the amount of numbers to sort: ";
    std::cin >> n;
    int arr[n];
    std::cout << "Enter " << n << " numbers: ";
    int num;

   
    for (int i = 0; i < n; i++) {
        std::cin >> num;
        arr[i] = num;
    }


	sortByFrequency(arr, n);

	return 0;
}
