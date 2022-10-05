/** "Making change" problem is based on greedy algorithm.
 * Here the key function is "find"
 */ 

#include<iostream>
using namespace std;

int find(int arr[], int n, int mon)
{
    int count =0;
    for(int i=n-1;i>=0;i--)
    {
        while(mon>=arr[i])
        {
            mon=mon-arr[i];
            count++;
        }
    }
    return count;
}

// Main function :

int main()
{
    int n;
    cout<<"Enter the number of coins : ";
    cin>>n;
    int arr[10],mon;
    cout<<"Enter the values of coins in ascending order : ";
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    cout<<"Enter the money value : ";
    cin>>mon;
    int res = find(arr,n,mon);
    cout<<"The number of coins required is : "<<res<<endl;
    return 0;
}