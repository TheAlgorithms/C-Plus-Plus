
//complexity of this is o(n2)

#include <iostream>
using namespace std;
//void reverseArray(int n ,int arr[]){
//	
//   for(int i=n-1;i>=0;i--){
//  
//        cout<<arr[i]<<" ";
//    }
//}
void sorting(int arr[], int size){
	int temp,min;
	for(int i=0;i<=size-1;i++){
		
		for(int j=i+1;j<size;j++){
			if(arr[i]>arr[j]){
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
				
			}
			
			
		}
	}
}
void kthSmall(int arr[], int size, int k){
	    sorting(arr,size);
//	   sort(arr.begin(),arr.end());
for(int i=0;i<size;i++){
	cout<<arr[i]<<" "<<endl;
	
    
}
 cout<<"Enter position which u want from an array=";
    cin>>k;
cout<<arr[k];
}

int main() {
    int size,k;
    cout<<"Enter the size of the array=";
    cin>>size;
    
    int arr[size];
    cout<<"Enter the elements of sn srrsy"<<endl;
    for(int i=0;i<size;i++){
    	
        cin>>arr[i];
        
    }
    kthSmall(arr,size,k);
    

    return 0;
}
