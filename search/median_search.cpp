/**
 * \file
 * \brief [Median search](https://en.wikipedia.org/wiki/Median_search) algorithm
 * cases from [here](https://brilliant.org/wiki/median-finding-algorithm/)
 * \ingroup median search
 */

#include <iostream>
#include <algorithm>
#include <vector>

/* Assume that all the elements of A are distinct
    def median_of_medians(A, i):

    #divide A into sublists of len 5
    sublists = [A[j:j+5] for j in range(0, len(A), 5)]
    medians = [sorted(sublist)[len(sublist)/2] for sublist in sublists]
    if len(medians) <= 5:
        pivot = sorted(medians)[len(medians)/2]
    else:
        #the pivot is the median of the medians
        pivot = median_of_medians(medians, len(medians)/2)

    #partitioning step
    low = [j for j in A if j < pivot]
    high = [j for j in A if j > pivot]

    k = len(low)
    if i < k:
        return median_of_medians(low,i)
    elif i > k:
        return median_of_medians(high,i-k-1)
    else: #pivot = k
        return pivot
*/

/*
 * Here are some example lists you can use to see how the algorithm works
 * A = [1,2,3,4,5,1000,8,9,99] (Contain Unique Elements)
 * B = [1,2,3,4,5,6] (Contains Unique Elements)
 * print median_of_medians(A, 0) #should be 1
 * print median_of_medians(A,7) #should be 99
 * print median_of_medians(B,4) #should be 5
*/

int median_of_medians(std::vector<int> a,  int idx){
	int pivot = 0;			// initialized with zero
	std::vector<int> m;
	int r = a.size();
	for(int i = 0; i < r; i += 5){
		std::sort(a.begin() + i, a.begin() + std::min(r, i + 5));
		int mid = (i + std::min(r, i + 5)) / 2;
		m.push_back(a[mid]);
	}
	int sz = int(m.size());
	if(sz <= 5){
		std::sort(m.begin(), m.end());
		pivot = m[(sz- 1) / 2];
	}
	else{
		pivot = median_of_medians(m, idx);
	}
	std::vector<int> low;
	std::vector<int> high;
	for(int i = 0; i < r; i++){
		if(a[i] < pivot){
			low.push_back(a[i]);
		}
		else if(a[i] > pivot){
			high.push_back(a[i]);
		}
	}
	int k = int(low.size());
	if(idx < k){
		return median_of_medians(low, idx);
	}
	else if(idx > k){
		return median_of_medians(high, idx-k-1);
	}
	else{
		return pivot;
	}
}

/* Main function*/

int main()
{
	int n = 0;
	std::cout << "Enter Size of Array: ";
	std::cin >> n;
	std::vector<int> a(n);
	std::cout << "Enter Array: ";
	for(int i = 0; i < n; i++){
		std::cin >> a[i];
	}
	std::cout << "Median: ";			// Median defination: https://en.wikipedia.org/wiki/Median
	int x = median_of_medians(a,  (n - 1) / 2);
	if(n % 2 == 0){
		int y = median_of_medians(a, n / 2);
		std::cout << (float(x) + float(y))/2.0;
	}
	else{
		std::cout << x;
	}
	std::cout << "\nTo find i-th smallest element ";
       	std::cout << "\nEnter i: ";
	int idx = 0;
	std::cin >> idx;
	idx--;
	std::cout << idx + 1<< "-th smallest element: " << median_of_medians(a, idx) << '\n';
	return 0;
}

