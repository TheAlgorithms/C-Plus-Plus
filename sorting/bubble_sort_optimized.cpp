
/*This version of bubble sort will reduce the number of passes needed if average cases and also the number od swaps needed in each pass which optimize the algorithm*/


#include <iostream>
#include <vector>
using namespace std;

vector<int>& bubble_sort(vector<int>& nums){
    int flag=0;
    int temp;
    for(int i=0; i<nums.size()-1;i++){
        flag=0;
        for(int j=0; j<nums.size()-1-i;j++){
             if(nums[j]>nums[j+1]){
                temp=nums[j];
                nums[j]=nums[j+1];
                nums[j+1]=temp;
                flag=1;
             }
        }
        if(flag==0){
            break;
        }
    }
    return nums;
}


int main() {
    vector<int> v={2,8,1,6,2,0,3,6};
    v=bubble_sort(v);
    for(int i=0;i<v.size();i++){
        cout<<v.at(i)<<endl;
    }
    return 0;
}