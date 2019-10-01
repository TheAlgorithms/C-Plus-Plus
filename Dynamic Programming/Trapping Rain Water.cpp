/*

Problem Description - https://leetcode.com/problems/trapping-rain-water/description/


Test Cases - 

Input: [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6


*/

#include<iostream>
#include<vector>
using namespace std;

int trapRainWater(int *arr, int n)
{
	if(n < 3)
    return 0;
        
    vector<pair<int,int>>indexes;
    
    for(int i = 0 ; i < n ; i++)
    {
        bool check = false;
        int j = i + 1;
        
        int maxVal = 0;
        int index = i + 1;
        
        for(; j < n ; j++) // finding the corresponding value for the given start index
        {
            if(maxVal <= arr[j])
            {
                maxVal = arr[j]; 
                index = j;
                
                if(maxVal >= arr[i]) // if current value exceeds or is equal to arr[i] break 
                break;
            }
        }
        
        if(index != i + 1)
        {
            pair<int,int>e;
            e.first = i;
            e.second = index; // insert it as a pair to show (start, end) for our water segment
            
            indexes.push_back(e);
            i = index - 1;
        }
    }
    
    int totalVol = 0;
    for(int i = 0 ; i < indexes.size() ; i++)
    {
        pair<int,int>p = indexes[i];
        int minHeight = min(arr[p.first], arr[p.second]); // choose the minimum of the two boundaries to get max height of water enclosed
        
        for(int j = p.first + 1 ; j < p.second ; j++)
        totalVol += abs(minHeight - arr[j]); // compute water stored corresponding to each cell inside a segment
    }
    
    return totalVol;        
}

int main()
{
	int n;
	cin>>n;

	int arr[n];
	for(int i = 0 ; i < n ; i++)
	cin>>arr[i];

	cout<<trapRainWater(arr, n)<<endl;
}