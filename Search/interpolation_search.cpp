#include<iostream>

#include<vector>

using namespace std;
template<typename T,typename T1,typename T2>
int interpolatio_n(T1 key,T arr[],T2 size){
int low=0,high=size-1;
while(low<=high && key>=arr[low] && key <=arr[high]){
    if(low==high){
        if(arr[low]==key) return low;
        return -1;
    }

    int pos=low+(key-arr[low])*(high-low)/(arr[high]-arr[low]);
    if(arr[pos]==key)
        return pos;
    if(arr[pos]>key)
        high=pos-1;
    if(arr[pos]<key)
        low=pos+1;



}
return -1;
}

template<typename p,typename p1  >
int interpolatio_n(p1 key,vector<p> arr){
int low=0,high=arr.size()-1;
while(low<=high && key>=arr[low] && key <=arr[high]){
    if(low==high){
        if(arr[low]==key) return low;
        return -1;
    }

    int pos=low+(key-arr[low])*(high-low)/(arr[high]-arr[low]);
    if(arr[pos]==key)
        return pos;
    if(arr[pos]>key)
        high=pos-1;
    if(arr[pos]<key)
        low=pos+1;



}
return -1;
}

int main(){

    vector<double> vec={1.2,2.3,5};
    double arr[]={5.2,6.1,8.9,80.6,91,122.32};
    cout<<interpolatio_n(5,vec)<<"" ;
    cout<<interpolatio_n(91,arr,6)<<"" ;






    return 0;
}
