#include<iostream>
using namespace std;
void InsertionSort(int *A, int n)
{
   int i, temp, j;
   for (i = 0; i < n; i++) {

      temp = A[i];
      j = i;

      while (j > 0 && temp < A[j - 1]) {
         A[j] = A[j - 1];
         j = j - 1;

      }
      A[j] = temp;
   }
}
void merge(int array[], int min, int max, int mid);
void mergeSort(int array[], int min, int max, int threshold)
{
   // prerequisite
   if ((max - min + 1) <= threshold)
   {
      InsertionSort(&array[min], max);
   }
   else
   {
      // get the middle point
      int mid = (max + min) / 2;

      // apply merge sort to both parts of this
      mergeSort(array, min, mid, threshold);
      mergeSort(array, mid + 1, max, threshold);

      // and finally merge all that sorted stuff
      merge(array, min, max, mid);
   }
}

void merge(int array[], int min, int max, int mid)
{
   int firstIndex = min;
   int secondIndex = mid + 1;
   int * tempArray = new int[max + 1];


   // While there are elements in the left or right runs
   for (int index = min; index <= max; index++) {
      // If left run head exists and is <= existing right run head.
      if (firstIndex <= mid && (secondIndex > max || array[firstIndex] <= array[secondIndex]))
      {
         tempArray[index] = array[firstIndex];
         firstIndex = firstIndex + 1;
      }

      else
      {
         tempArray[index] = array[secondIndex];
         secondIndex = secondIndex + 1;
      }

   }

   // transfer to the initial array
   for (int index = min; index <= max; index++)
      array[index] = tempArray[index];
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
   mergeSort(_array, 0, size ,20);

   //output
   for (int i = 0; i < size; ++i)
   {
      cout << _array[i] << "\t";
   }


   delete[] _array;
   return 0;
}
