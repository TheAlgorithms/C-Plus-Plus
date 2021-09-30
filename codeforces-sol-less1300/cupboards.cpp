#include<iostream>
#include<math.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    int col1_open=0;
    int col1_close=0;
    int col2_open=0;
    int col2_close=0;
    int arr[n][2];
    for(int i=0;i<n;i++){
        for(int j=0;j<2;j++){
            cin>>arr[i][j];
            if(j==0){
                if(arr[i][j]==1)
                col1_open++;
                else
                col1_close++;
            }else{
                if(arr[i][j]==1){
                    col2_open++;

                }else{
                    col2_close++;
                }
            }
        }
    }
    cout<<min(col1_open,col1_close)+min(col2_close,col2_open);
    
}