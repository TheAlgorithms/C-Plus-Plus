/*
  Activity Selection Problem is a combinatorial optimization problem concerning the selection of non-conflicting activities, given their starting and finishing times. The problem is to select the maximum number of activities that can be performed by a single resource, assuming that only a single activity can use that resource at a time. A classic application of this problem is in scheduling a room for multiple competing events, or a resource for a process queue, each having its own time requirements (start and end time).
  
  This is a classic example of problem that can be solved by using the greedy-choice heuristic. What do we mean by the greedy choice for the activity-selection problem? Intuition suggests that we should choose an activity that leaves the resource available for as many other activities as possible. Hence, we must pick the activity which will finish first, because it will leave maximum amount of time for other resources.
  
  For example, assume we have 5 activities that wish to share a resource, along with their starting and finishing times:
      
      i |   START  |  FINISH
    ----+----------+-----------
      0 |     1    |    2
      1 |     2    |    4
      2 |     5    |    7
      3 |     3    |    4
      4 |     2    |    3
          
   The maximum possible number of activities that can be done is 3: activities 0, 2, and 4 can done without any conficts. Activities 0, 2, and 3 also make a valid answer set.

  _________________________________________________________________________
  Reference: Introduction to Algorithms (Cormen, Leiserson, Rivest, Stein).
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;


/*
  This is a custom comparator function, that will sort a vector of pairs upon the basis of their finishing times.
  
  Therefore, the vector {(1,2), (2,4), (5,7), (3,4), (2,3)} will become {(1,2), (2,3), (2,4), (3,4), (5,7)} after it runs through the comparator function.
*/
static bool compare(pair<int,int> a, pair<int, int> b){
    if(a.second==b.second){
        return a.first < b.first;
    }
    return a.second < b.second;
}


/*
  The main problem solving function. The activity-selection problem takes in input the number of activities, n, along with their starting and finishing times.
  
  For any activity i, start[i] represents its starting time, and finish[i] is the time at which activity will finish.
*/
int activitySelection(vector<int> start, vector<int> finish, int n){
    vector<pair<int,int>> times;  // make a vector of pairs, with pair (start[i], finish[i]) denoting starting and finishing times for activity i.
    for(int i=0;i<n;i++){
        times.push_back(make_pair(start[i],finish[i]));
    }
    sort(times.begin(),times.end(), compare); // We sort the times vector on basis of the finishing time.
    
    int max_activities = 0; // maximum number of activities we can possibly perform, the solution to our problem.
    int curr_time = 0; // the current time, used to keep track of which activity is next
    for(int i=0;i<n;i++){
        if(times[i].first>curr_time){ // Checking if it is possible to start this activity. If yes, we do it and current time is set to the time the activity is done with.
            max_activities++;
            curr_time = times[i].second;
        }
    }
    return max_activities;  // retuns the number of maximum possible activities.
}

/*


Example of test input:
5
1 2
2 4
5 7
3 4
2 4

Output:
3

*/
int main() {
	int n;  // Number of activities
    cout<<"Enter the number of activities: ";
	cin>>n;
    cout<<endl;
	vector<int> start(n), finish(n);  // Will stores starting and finishing times.
    cout<<"Enter starting and finishing times for each actvity: ";
	for(int i=0;i<n;i++){
	    cin>>start[i]>>finish[i]; // Enter the starting and finishing times for activity i.
	}
	cout<<activitySelection(start, finish, n)<<endl;  // Solve the problem and output the answer.
	return 0;
}
