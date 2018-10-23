//Bubble Sort

#include<iostream>
using namespace std;

int main(){
	int n, temp;
	cout<<"Enter size of Array = ";
	cin >> n;
	int *Array = new int[n];
	cout<<"\nEnter any " <<n <<" Numbers for Unsorted Array :\n";

	//Input
	for(int i=0; i<n; i++){
		cout<<"value " <<(i+1) <<" = ";
		cin>>Array[i];
	}

	//Bubble Sorting
	for(int i=n; i>0; i--){
		for(int j=0; j<i; j++){ // Array[i..n] is already sorted
			if(Array[j]>Array[j+1]){
				temp=Array[j];
				Array[j]=Array[j+1];
				Array[j+1]=temp;
			}
		}
	}

	//Output
	cout<<"\nSorted Array : ";
	for(int i=0; i<n; i++)
		cout<<Array[i]<<"\t";
	return 0;
}
