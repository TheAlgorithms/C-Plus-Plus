#include<iostream>
using namespace std;

void rankSort(int arr[],int n){
    int rank[n];
    int out[n];

    for(int i=0;i<n;i++){
        rank[i] = 0;
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(arr[i]>arr[j])
                rank[i]++;
        }
    }

    for(int i=0;i<n;i++){
        out[rank[i]] = arr[i];
    }

    cout<<"\nSorted Array : \n";
    for(int i=0;i<n;i++){
        cout<<out[i]<<" ";
    }
    cout<<endl;

}

int main(){
    int n;
    cout<<"enter the number of elements : ";
    cin>>n;
    int arr[n];
    cout<<"enter the elements\n";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    rankSort(arr,n);

return 0;
}
