#include<iostream>
#include<vector>
using namespace std;
int main(){
    int n,t=1;
    cin>>n;
    int i=0;
    int temp;
    int num[100];
    if(n%2!=0){
        cout<<-1;
    }else{
        while(t<=n){
            num[i]=t;
            t++;
            i++;

        }
       
        for(int k=0;k<i;k++){
            temp=num[k];
            num[k]=num[k+1];
            num[k+1]=temp;
            k++;

        }
         for(int j=0;j<i;j++){
            cout<<num[j]<<" ";
        }
        
    }
}