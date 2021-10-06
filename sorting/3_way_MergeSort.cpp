// C++ Program to perform 3 way Merge Sort
#include <bits/stdc++.h>
using namespace std;

/* Merge the sorted ranges [low, mid1), [mid1,mid2)
and [mid2, high) mid1 is first midpoint
index in overall range to merge mid2 is second
midpoint index in overall range to merge*/
void merge(int gArray[], int low, int mid1,
		int mid2, int high, int destArray[])
{
	int i = low, j = mid1, k = mid2, l = low;

	// choose smaller of the smallest in the three ranges
	while ((i < mid1) && (j < mid2) && (k < high))
	{
		if(gArray[i] < gArray[j])
		{
			if(gArray[i] < gArray[k])
			{
				destArray[l++] = gArray[i++];
			}
			else
			{
				destArray[l++] = gArray[k++];
			}
		}
		else
		{
			if(gArray[j] < gArray[k])
			{
				destArray[l++] = gArray[j++];
			}
			else
			{
				destArray[l++] = gArray[k++];
			}
		}
	}

	// case where first and second ranges
	// have remaining values
	while ((i < mid1) && (j < mid2))
	{
		if(gArray[i] < gArray[j])
		{
			destArray[l++] = gArray[i++];
		}
		else
		{
			destArray[l++] = gArray[j++];
		}
	}

	// case where second and third ranges
	// have remaining values
	while ((j < mid2) && (k < high))
	{
		if(gArray[j] < gArray[k])
		{
			destArray[l++] = gArray[j++];
		}
		else
		{
			destArray[l++] = gArray[k++];
		}
	}

	// case where first and third ranges have
	// remaining values
	while ((i < mid1) && (k < high))
	{
		if(gArray[i] < gArray[k])
		{
			destArray[l++] = gArray[i++];
		}
		else
		{
			destArray[l++] = gArray[k++];
		}
	}

	// copy remaining values from the first range
	while (i < mid1)
		destArray[l++] = gArray[i++];

	// copy remaining values from the second range
	while (j < mid2)
		destArray[l++] = gArray[j++];

	// copy remaining values from the third range
	while (k < high)
		destArray[l++] = gArray[k++];
}


/* Performing the merge sort algorithm on the
given array of values in the rangeof indices
[low, high). low is minimum index, high is
maximum index (exclusive) */
void mergeSort3WayRec(int gArray[], int low,
					int high, int destArray[])
{
	// If array size is 1 then do nothing
	if (high - low < 2)
		return;

	// Splitting array into 3 parts
	int mid1 = low + ((high - low) / 3);
	int mid2 = low + 2 * ((high - low) / 3) + 1;

	// Sorting 3 arrays recursively
	mergeSort3WayRec(destArray, low, mid1, gArray);
	mergeSort3WayRec(destArray, mid1, mid2, gArray);
	mergeSort3WayRec(destArray, mid2, high, gArray);

	// Merging the sorted arrays
	merge(destArray, low, mid1, mid2, high, gArray);
}

void mergeSort3Way(int gArray[], int n)
{
	// if array size is zero return null
	if (n == 0)
		return;

	// creating duplicate of given array
	int fArray[n];

	// copying alements of given array into
	// duplicate array
	for (int i = 0; i < n; i++)
		fArray[i] = gArray[i];

	// sort function
	mergeSort3WayRec(fArray, 0, n, gArray);

	// copy back elements of duplicate array
	// to given array
	for (int i = 0; i < n; i++)
		gArray[i] = fArray[i];
}

// Driver Code
int main()
{
	int data[] = {45, -2, -45, 78, 30,
				-42, 10, 19, 73, 93};
	mergeSort3Way(data,10);
	cout << "After 3 way merge sort: ";
	for (int i = 0; i < 10; i++)
	{
		cout << data[i] << " ";
	}
	return 0;
}

