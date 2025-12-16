#include <iostream>
using namespace std;

bool isPalindrome(int num) {
    if(num<0) {
        return false;
    }
    int temp=num, rev=0;
    while(temp!=0) {
        rev=rev*10 + temp%10;
        temp=temp/10;
    }
    if(rev==num) {
        return true;
    }
    return false;
}

int main() {
    int num;
    cout << "Enter an integer : " << endl;
    cin >> num;
    
    cout << isPalindrome(num);
    return 0;
}