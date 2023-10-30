/* question we have to find out which elemnting is repeating in given array
if element present more than 1 time then it called as repeating element
EX:arr[]={0,2,1,3,2,2}
o/p:2 
there are some condition to solve the question 
1)find out max element in an array for above ex it is equal to 3 
must that array contain element from(0 to 3){0,2,1,3,2,2}
must follow below things
1) time complexity O(n)
2) space complexity O(1)
3)no modification to orginal array
*/
#include<iostream>
using namespace std;
/* super navie solution: time complexity O(n^2) and and space complexity O(1)  */
/*int  super_navie_repeating(int arr[],int n){
    for(int i=0;i<n-1;i++){
          for(int j=i+1;j<n;j++){
            if(arr[i]==arr[j]){
                return arr[i];
            }
          }
    }
    return 0;
}*/
/* navie solution  time complexity O(nlogn) and space complexity O(1)
steps: 1)sort the array 
2) if any two consective element equal then return that number*/
void merge(int arr[], int low, int q, int high)
{
    int n1 = q - low + 1;
    int n2 = high - q;
    int leftarray[n1 + 1], rightarray[n2 + 1];
    for (int i = 0; i < n1; i++)
    {
        leftarray[i] = arr[i + low];
    }
    for (int j = 0; j < n2; j++)
    {
        rightarray[j] = arr[q + j + 1];
    }
    leftarray[n1] = INT16_MAX;
    rightarray[n2] = INT16_MAX;
    int i = 0, j = 0;
    for (int k = low; k <= high; k++)
    {
        if (leftarray[i] <= rightarray[j])
        {
            arr[k] = leftarray[i];
            i++;
        }
        else
        {
            arr[k] = rightarray[j];
            j++;
        }
    }
}

void merge_sort(int arr[], int low, int high)
{
    if (low < high)
    {
        int q = (low + high) / 2;
        merge_sort(arr, low, q);
        merge_sort(arr, q + 1, high);
        merge(arr, low, q, high);
    }
}
int navie_solution(int arr[],int n){
    merge_sort(arr,0,n-1);
    for(int i=0;i<n-1;i++){
        if(arr[i]==arr[i+1]){
            return arr[i];
        }
    }
    return 0;
}
int main()
{
    int arr[]={0,2,1,3,2,2};
    //cout<< super_navie_repeating(arr,6);
    cout<<navie_solution(arr,6);
 return 0 ;
}