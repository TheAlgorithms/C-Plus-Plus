#include <iostream>
#include <climits>
using namespace std;
 int main(){
        int arr []={-1,-2,3,-4};
        int max=0,curr=0,neg=INT_MIN;
        for (int value : arr) {
            curr += value;
            if (curr > max)
                max = curr;
            else if (curr < 0)
                curr = 0;
            if(neg<value)
                neg=value;
        }
        if(neg>0)
           cout<<max;
        else
           cout<<neg;
}

