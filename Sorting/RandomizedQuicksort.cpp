/* C implementation Randomized-QuickSort */
#include<iostream>
#include<stdlib.h>

#define random(x, y) (rand()%(y-x)+x)
using namespace std;
 
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <high; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            int temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }
    }
    int temp=arr[i+1];
    arr[i+1]=arr[high];
    arr[high]=temp;
    return (i + 1);
}
 
int Randomized_Partition(int arr[], int low, int high){
    int i = random(low, high);
    int tmp = arr[high-1];
    arr[high-1] = arr[i];
    arr[i] = tmp;
    return partition(arr, low, high);
}

 
 void Randomized_QuickSort(int arr[], int low, int high){
    if (low < high)
    {
      
        int p= Randomized_Partition(arr, low, high);
        Randomized_QuickSort(arr, low, p - 1);
        Randomized_QuickSort(arr, p + 1, high);
    } 
 }

void show(int arr[], int size)
{
    for (int i=0; i < size; i++)
    cout<<arr[i]<<"\n";
}
 
// Driver program to test above functions
int main()
{
    int size;
    cout<<"\nEnter the number of elements : ";

    cin>>size;

    int arr[size];
    
    cout<<"\nEnter the unsorted elements : ";

    for (int i = 0; i < size; ++i)
    {
        cout<<"\n";
        cin>>arr[i];
    }
    Randomized_QuickSort(arr, 0, size);
    cout<<"Sorted array\n";
    show(arr, size);
    return 0;
}