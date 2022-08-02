<!-- Table of content -->
# Table of content
- [Searching Algorithms](#searching-algorithms)
   -  [Linear Search](#linear-search)
       - [Code](#code)
       - [Properties](#properties)
       - [Advantages](#advantages)
       - [Disadvantage](#disadvantage)
       ## Linear Search

- Start from the zero index of array and one by one compare Search Element(X) with each element of arr[].
-  If Search Element(X) matches with an element of the arr[], return the index.
-  If Search Element(X) doesn’t match with any of elements, then return -1.
<!-- image to help better explain the concept -->

![linear_search](https://user-images.githubusercontent.com/88760648/158869345-bce5e75c-57f8-4604-9c5e-f57650c3dfdb.gif)
n
## Some More Example
![linearsearchalgorithim](https://user-images.githubusercontent.com/88760648/158868400-013fdfd5-0acf-4653-bc57-ed79572c08a6.jpeg)
<!-- citation : [Here](https://www.tutorialspoint.com/data_structures_algorithms/linear_search_algorithm.htm)  -->

<!-- citation : [Here](https://thecleverprogrammer.com/2020/09/10/linear-search-algorithm-with-python/)  -->

### Code

```

// C++ code to linearly search x in arr[]. If search ELement (x)
// is present then return its Index, otherwise
// return -1
#include <iostream>
using namespace std;

int search(int arr[], int n, int searchkey)
{
	
	for (int i = 0; i < n; i++)
		if (arr[i] == searchkey)
			return i;
	return -1;
}

// Driver code
int main()
{
	int arr[] = { 2, 3, 4, 10, 40 };
	int searchkey; // = 10;
    cin>> searchkey;
	int n = sizeof(arr) / sizeof(arr[0]);

	// Function call
	int result = search(arr, n, searchkey);
	(result == -1)
		? cout << "Element is not present in array"
		: cout << "Element is present at index " << result;
	return 0;
}


```
### Properties

- Time Complexity : O(n)
- Space Complexity : O(1)
- It has a very simple implementation.

### Advantages

- The list does not need to sorted

### Disadvantage

- Inversely, slow searching of big lists.

