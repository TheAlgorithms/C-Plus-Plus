#include<bits/stdc++.h>
using namespace std;
int main(){
    vector<int> A = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int sum = A[0];
    int finalSum = sum;
    for(int i=1;i<A.size();i++){
        sum = sum+A[i];
        if(sum<0){
            sum = max(sum,A[i]);
            finalSum = max(finalSum,sum);
            sum = 0;
        }
        else{
            finalSum = max(sum,finalSum);
        }

    }
    cout<<" finalSum = "<<finalSum<<endl;
}