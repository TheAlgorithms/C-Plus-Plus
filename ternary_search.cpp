int three_part_binary_search(int a[], int x, int low, int high){
	
	if (low < high){
		int m1 = (low + high) / 3 + 1;
		int m2 = 2 * (low + high) / 3 + 1;

		if (x == a[m1])
			return m1;
		else if (x == a[m2])
			return m2;
		else if (x < a[m1])
			return three_part_binary_search(a, x, low, m1 - 1);
		else if (x < a[m2])
			return three_part_binary_search(a, x, m1 + 1, m2 - 1);
		else if (x > a[m2])
			return three_part_binary_search(a, x, m2 + 1, high);
	}
	else
		return -1;
}

/*
Ternary Search Working Principle
	Like linear search and binary search, ternary search is a searching technique that 
is used to determine the position of a specific value in an array. In binary search, 
the sorted array is divided into two parts while in ternary search, 
it is divided into 3 parts and then you determine in which part the element exists.
	Ternary search, like binary search, is a divide-and-conquer algorithm. 
It is mandatory for the array (in which you will search for an element) to be sorted 
before you begin the search. In this search, after each iteration it neglects ⅓
part of the array and repeats the same operations on the remaining ⅔ .
*/
