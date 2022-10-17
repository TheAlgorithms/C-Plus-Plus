//Max subarray sum using Kadanes algorithm

#include <iostream>
using namespace std;

int main()
{
	int arr_size; cin>>arr_size;
	int arr[arr_size];
	for(int i=0;i<arr_size;++i) cin>>arr[i];

	int ma=0,ans=INT_MIN;
	for(int i=0;i<arr_size;++i){
		ma+=arr[i];
		if(ma>ans){
			ans=ma;
		}
		if(ma<0) ma=0;
	}
	cout<<ans<<endl;
	
	return 0;
}
