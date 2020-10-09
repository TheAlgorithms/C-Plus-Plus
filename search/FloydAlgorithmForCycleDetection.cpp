
/*Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.

If there is only one duplicate number in nums, this algo returns the duplicate number in O(1) space and time complexity less than O(n^2) without modifying the original array.

Example-:
    Input:-  Enter nos=3 4 8 5 9 1 2 6 7 4
    
    Output: Duplicate number=4
*/
#include<iostream>
#include<array>
    int findDuplicate(std::array <int,10> nums) {
        int slow=nums[0];
        int fast=nums[0];
        do{
            slow=nums[slow];
            fast=nums[nums[fast]];
        }while(slow!=fast);
        slow=nums[0];
        while(slow!=fast)
        {
            slow=nums[slow];
            fast=nums[fast];
        }
        return slow;
    }
int main()
{ 
    std::array <int,10 > arr;
    int ans;
	std::cout<<"Enter nos=";
	for(int temp, i = 0; i < arr.size() && std::cin >> temp; ++i) {
        arr[i] = temp;
    }
    ans=findDuplicate(arr);
    std::cout<<"\nDuplicate number="<<ans;
    return 0;
}
