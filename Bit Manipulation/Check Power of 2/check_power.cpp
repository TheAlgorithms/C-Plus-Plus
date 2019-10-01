#include <iostream>
using namespace std;
int check(int n){
    if(n==0) return 0;
    if((n&(n-1)) == 0) return 1;
    else return -1;
}
int main(){
    int n;
    cin >> n;
    if(check(n) == 0){
        cout << "Number is 0";
    }
    else if(check(n) == -1){
        cout << "Number is not a power of 2";
    }
    else{
        cout << "Number is a power of 2";
    }
    return 0;
}