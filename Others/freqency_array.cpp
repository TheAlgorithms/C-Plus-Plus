#include<iostream> 

using namespace std;

void printfrequency(int arr[],int n) 
{  
    for (int j =0; j<n; j++) 
        arr[j] = arr[j]-1;  
    for (int i=0; i<n; i++) 
        arr[arr[i]%n] = arr[arr[i]%n] + n; 
   
    for (int i =0; i<n; i++) 
        cout << i + 1 << " ->  " << arr[i]/n << endl; 
} 

int main()
{
	int n;
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++)
		{
			cin>>a[i];
			
		}
		printfrequency(a,n); 
		return 0;
}
