#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int medianOfThree(int *d, int low, int high)
{
	   int mid = low + (high - low) / 2;
	      if (d[low] <= d[mid] && d[mid] <= d[high]) return d[mid];
	         if (d[high] <= d[mid] && d[mid] <= d[low]) return d[mid];

		    if (d[mid] <= d[low] && d[low] <= d[high]) return d[low];
		       if (d[high] <= d[low] && d[low] <= d[low]) return d[low];

		          return d[high];

}
void quicksort(int* d, int fir, int last) {
	   int left = fir;
	      int right = last;
	         int pivot = fir + rand() % (last - fir + 1);

		    do {
			          while (d[left] < pivot) left++;
				        while (d[right] > pivot) right--;
					      if (left <= right) {
						               int temp = d[left];
							                d[left] = d[right];
									         d[right] = temp;
										          left++;
											           right--;
												         }
					         } while (left <= right);
		       if (fir < right) {
			             quicksort(d, fir, right);
				           quicksort(d, left, last);
					      }

}


int main()
{
	   int size = 10;
	      int *_array = new int[size];
	         //input
		    for (int i = 0; i < size; i++)
		       {
		             cin >> _array[i];
		                }
		                   srand(time(NULL));
		                      quicksort(_array, 0, size - 1);
		 
		 //                        //output
		                            for (int i = 0; i < size; ++i)
		                               {
		                                     cout << _array[i] << "\t";
		                                        }
		 
		 
		                                           delete[] _array;
		                                              return 0;
		                                            }
