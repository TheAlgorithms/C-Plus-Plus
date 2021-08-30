//Cycle sort

/* This method of sorting can be applied when we are given some range of numbers like [0,n] or [1,n] 

I want to mention 2 most popular question asked in Amazon interview:-
https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
https://leetcode.com/problems/missing-number/

*/

  static void swap(int[] arr, int f, int l){
        int var = arr[f];
        arr[f] = arr[l];
        arr[l] = var;
    }
    
int cycleSort(){
int i=0;
        while(i<nums.length){
            int correct = nums[i];
            if(nums[i] < len && nums[i] != nums[correct]){
                swap(nums,i,correct);
            }
            else{
                i++;
            }
        }
        
        for(i=0; i<len; i++){
            if(nums[i] != i){
                return i;
            }
        }
  return -1;
}

/*
Note:- There is only the function of code that has to be called inside main function.
*/
