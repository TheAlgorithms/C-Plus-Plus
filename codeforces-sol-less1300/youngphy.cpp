#include<iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    int arr[n][3];
    int sum1=0,sum2=0,sum3=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<3;j++){
            cin>>arr[i][j];
            if(j==0)
            sum1=sum1+arr[i][j];
            if(j==1)
            sum2=sum2+arr[i][j];
            if(j==2)
            sum3=sum3+arr[i][j];
        }
    }
    if(sum1==0&&sum2==0){
        if(sum3==0)
        cout<<"YES";
        else{
            cout<<"NO";
        }
    }else{
        cout<<"NO";
    }

}