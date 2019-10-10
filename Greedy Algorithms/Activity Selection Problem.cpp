/*
PROBLEM : We are given N activities having starting time and finishing time. Assuming that
a person can perform a single activity at a time, we have to select maximum number of activities that
can be performed without a conflict i.e. starting time of the chosen activity should be greater than or
equal to finish time of its previous activity.
SOLUTION : We use greedy approach to solve this problem. First we sort the activities in ascending
order of their finishing time then we choose non-conflicting activities one by one from minimum
finish time to maximum and drop the rest.
*/
#include<iostream>
#include<algorithm>
using namespace std;
class activity //represents an activity
{
   public:
   long st; //starting time of an activity
   long ft; //finishing time of an activity
};
bool compare(activity a1, activity a2) //compare function for sorting activities in ascending order of finishing time
{
    return (a1.ft < a2.ft);
}
int main()
{
    int N;
    long act = 1; //at least one activity (with minimum finish time) can be performed
    cout<<"Enter the total number of activities : ";
    cin>>N;   //total number of activities
    activity a[N];  //array of activities each having a starting and finishing time
    for(int i=0; i < N; i++)
    {
        cout<<"\nEnter starting time and finishing time of activity "<<i+1<<" : ";
        cin>>a[i].st>>a[i].ft;
    }
    sort(a, a+N, compare);
    long current_ft = a[0].ft;
     cout<<"Activity 1 can be performed"<<endl;
    for(int i=0; i < N; i++)
    {
        if(current_ft <= a[i].st)//checking whether the starting time of the activity is passed or not
           {
               cout<<"Activity "<<i+1<<" can be performed"<<endl;
               act++; //if true then this activity can be performed
               current_ft = a[i].ft; //recent finishing time is the finish time of this performed activity
           }
    }
    cout<<"Total "<<act<<" activities can be performed";  //total number of activities that can be performed without conflict
    return 0;
}
