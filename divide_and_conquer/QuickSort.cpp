#include <iostream>
using namespace std;

int Partition(int *arr, int s, int e){

    int pivot = arr[s];

    int count = 0;

    for(int i=s+1;i<=e;i++){
        if(arr[i] <= pivot){
            count++;
        }
    }

    int pivotindex = s + count;
    swap(arr[s],arr[pivotindex]);

    int i=s,j=e;

    while(i<pivotindex && j>pivotindex){
        while(arr[i] <= pivot)
            i++;

        while(arr[j] > pivot)
            j--;
        
        if(i<pivotindex && j>pivotindex)
            swap(arr[i++],arr[j--]);
    }

    return pivotindex;
}

void QuickSort(int *arr, int s, int e){
    
    if(s>=e)
        return;

    int p = Partition(arr,s,e);

    QuickSort(arr,s,p-1);
    QuickSort(arr,p+1,e);

}

int main(){
    int arr[6] = {15,6,13,5,12,9};
    int n = 6;

    QuickSort(arr, 0 ,n-1);

    for(int i=0; i<n;i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
