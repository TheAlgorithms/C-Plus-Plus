#include <iostream>
using namespace std;

void cyclicSort(int arr[], int n){
int i = 0;
while(i < n)
{
	
	int correct = arr[i] - 1 ;
	if(arr[i] != arr[correct]){

	swap(arr[i], arr[correct]) ;
	}else{

	i++ ;
	}
}

}

void printArray(int arr[], int size)
{
int i;
for (i = 0; i < size; i++)
	cout << arr[i] << " ";
cout << endl;
}

int main() {

int arr[] = { 3, 2, 4, 5, 1};
int n = sizeof(arr) / sizeof(arr[0]);
cout << "Before sorting array: \n";
printArray(arr, n);
cyclicSort(arr, n);
cout << "Sorted array: \n";
printArray(arr, n);
return 0;

}
