#include<iostream>
using namespace std;

int search(int arr[],int value,int len)		//function to search the value in an array using interpolation search
{
	int low=0,high,mid;
	high=len-1;
	while(arr[low]<=value and arr[high]>=value)
		{
			mid=(low + (( value-arr[low])*(high-low)) / (arr[high]-arr[low]));
			if(arr[mid]>value)
				high=mid-1;
			else if (arr[mid]<value)
				low=mid+1;
			else
				return mid; 
		}
	if(arr[low]== value)
		return low;
	return 0;
}

int main() 		//main function
{
	int n,value,array[100],re;
	cout<<"Enter the size of array(less than 100) : ";
	cin>>n;
	cout<<"Enter the values of array in ascending (increasing) order : "<<endl;
	
	for(int i=0;i<n;i++)
		cin>>array[i];

	cout<<"Enter the value you want to search : ";
	cin>>value;
	re=search(array,value,n);

	if(re==0)
		cout<<"Entered value is not in the array"<<endl;
	else	
		cout<<"The value is at the position "<<re<<endl;
	return 0;
}
