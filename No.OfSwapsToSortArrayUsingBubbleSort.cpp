#include<iostream>

using namespace std;

int main()
{
    int num, temp;
    cout<<"Enter the size of array:"<<endl;
    cin>>num;
    int arr[num];
    cout<<"Enter the elements of an array:"<<endl;
    for(int i=0;i<num;i++){
        cin>>arr[i];
    }

    int count =0;
    for(int i=0;i<num;i++){
        for( int j=0;j<num-i-1;j++){
                if(arr[j]>arr[j+1]){
                    temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                    count++;
                }
        }
    }
    cout<<"No.of swaps:"<<endl;
    cout<<count;
    return 0;
}
