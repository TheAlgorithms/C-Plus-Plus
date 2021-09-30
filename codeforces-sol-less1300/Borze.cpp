#include<iostream>
using namespace std;
int main(){
    string c="";
    char arr[200];
    int i=0,d;
   do
    {
        d = getchar();
        arr[i] = char(d);
        i++;
    } while(d!='\n');

    for(int k=0;k<i-1;k++){
        if(arr[k]=='.'){
           c=c+"0";

        }
        if(arr[k]=='-'&&arr[k+1]=='.'){
        k++;
        c=c+"1";
        }
        if(arr[k]=='-'&&arr[k+1]=='-'){
        k++;
        c=c+"2";

        }
    }
    cout<<c;
}