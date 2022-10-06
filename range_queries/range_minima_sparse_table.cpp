/*This Program finds the minimum element in the subarray defined by the provided indexes(0-based indexing)
in constant query time and O(Nlog(N)) build time using sparse table algorithm. The space complexity required
is O(Nlog(N)), where N is the input size.*/


#include<iostream> //for input/output
#include<math.h>   //for minimum operation

using namespace std;

int main()
{
	long long int size, query_count; //size stores te input size, query count stores number of queries
	cin>>size;

	long long int log_base_2[size+1], input_array[size], temp1 = 1, temp2 = 0; //arrays for storing input and logarithms
	log_base_2[0] = -1;

	for(long long int i = 1; i <= size; i++) //precompute logarithms base 2 for better query time
	{
		if(2 * temp1 <= i)
		{
			temp1 *= 2;
			temp2++;
		}
		log_base_2[i] = temp2;
	}

	for(long long int i = 0; i < size; i++) //store input in an array
		cin>>input_array[i];

	long long int Sparse_Table[size][log_base_2[size] + 1]; //Sparse table in 2d matrix, Nlog(N) size
	for (long long int i = 0; i < size; i++)
	    Sparse_Table[i][0] = input_array[i];

	for (int j = 1; j <= log_base_2[size]; j++) //Compute the matrix that will be used to achieve the task
	    for (long long int i = 0; i + (1 << j) <= size; i++)
	        Sparse_Table[i][j] = min(Sparse_Table[i][j-1], Sparse_Table[i + (1 << (j-1))][j - 1]);


	cin>>query_count;
	while(query_count--) //query loop
	{
		long long int left, right; //left and right indexes to define the subarray (0-indexed)
		cin>>left>>right;

		long long int log = log_base_2[right - left + 1];
		long long int minimum = min(Sparse_Table[left][log], Sparse_Table[right - (1 << log) + 1][log]);

		cout<<minimum<<"\n";
	}
}