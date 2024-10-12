#include<bits/stdc++.h>
using namespace std;

int main(){ 
    string numbers = "12345"; 
    int sum = 0;
    for(int i=0;i<numbers.size();i++){
       sum+=numbers[i]-'0';
    } 
    cout<<sum;
    return 0;
}