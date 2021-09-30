#include<iostream>
using namespace std;
int main(){
    int arr[100],prr[100];
    int c;
    int i=0,j=0;
    do{
        c=getchar();
        arr[i]=c;
        i++;
    }while(c!='\n');
    do{
        c=getchar();
        prr[j]=c;
        j++;
    }while(c!='\n');
    int crr[i-1];
    for(int k=0;k<i-1;k++){
        if(arr[k]==prr[k])
        crr[k]=0;
        else
        crr[k]=1;
        cout<<crr[k];
    }
}