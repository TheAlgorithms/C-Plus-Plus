#include<bits/stdc++.h>
//tower of hanoi algorithum..
using namespace std;
void steps(int disks,char source,char helper,char destination){
    if(disks==1){
        cout << disks << " disk transfer from " << source << " to " << destination<<endl;
        return;
    }
    steps(disks - 1, source, destination, helper);
    cout << disks << " disk transfer to " << source << " to " << destination<< endl;
    steps(disks - 1, helper, source, destination);
}
int main(){
    int disks;
    cout << "Enter the no. of disks: ";
    cin >> disks;
    steps(disks,'s','h','d');
    return 0;
}
