//Jump Game:
/*Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Determine if you are able to reach the last index.*/

#include <vector>
#include<iostream>
using namespace std;
bool canJump(vector<int> nums) {
    int lastPos = nums.size() - 1;
    for (auto i = nums.size() - 1; i >= 0; i--) {
        if (i + nums[i] >= lastPos) {
            lastPos = i;
        }
    }
    return lastPos == 0;
}

void main(){
    //Sample test case
    vector<int> num={4,3,1,0,5};
    cout<<canJump(num);  //Should display true, as when you take one step from position 0, you reach position 1, from which 3 steps lead you to the destination
}
