/*The difference of the sets A and B in this order is the set of elements which belong to A but not to B. 
Symbolically, we write A – B and read as “ A minus B”.
The set which contains the elements which are either in set A or in set B but not in both is called the symmetric difference between two given sets.
It is represented by A ⊝ B and is read as a symmetric difference of set A and B.
*/


#include <iostream>
using namespace std;

int main() {
    int x,y;
    cout<<"Enter number of elements in set first: "<<endl;
    cin>>x;
    cout<<"Enter number of elements in set second : "<<endl;
    cin>>y;
    int a[x],b[y];
    int  c[1000]={0};
    cout<<"Enter the elements in  first set: \n";
    for(int i=0;i<x;i++){
        cin>>a[i];
    }
    cout<<"Enter the elements in second set: \n";
    for(int i=0;i<y;i++){
        cin>>b[i];
    }
    for(int i=0;i<x;i++){
        c[a[i]]++;
    }
    for(int i=0;i<y;i++){
        c[b[i]]++;
    }
    cout<<"The symmetric difference of two given sets is (AΔB) : \n";
    for(int i=0;i<1000;i++){
        if(c[i]==1){
            cout<<i<<" ";
        }
    }

    return 0;
}
