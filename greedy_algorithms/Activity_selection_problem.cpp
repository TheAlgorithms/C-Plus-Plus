/*************Problem Statement************
There is one meeting room in a firm. There are N meetings in the form of (start[i], end[i]) where start[i] is start time of meeting i and end[i] is finish time of meeting i.
What is the maximum number of meetings that can be accommodated in the meeting room when only one meeting can be held in the meeting room at a particular time?

Note: Start time of one chosen meeting can't be equal to the end time of the other chosen meeting*/

// by Siddharth Singh {https://github.com/Siddharth189}
/******* Code Solution **********/
#include <bits/stdc++.h>
using namespace std;


class Solution
{
    public:
    //Function to find the maximum number of meetings that can
    //be performed in a meeting room.
    int maxMeetings(int start[], int end[], int n)
    {
        vector <pair<int, int>> vect;
        for(int i = 0; i < n; i++){
            vect.push_back(make_pair(end[i], start[i]));
        }
        sort(vect.begin(), vect.end());
        int na = 1;
        int k = 0;
        for(int i = 1; i < n; i++){
            if(vect[i].second > vect[k].first){
                na++;
                k = i;
            }
        }

        return na;
    }
};
 
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int start[n], end[n];
        for (int i = 0; i < n; i++) cin >> start[i];

        for (int i = 0; i < n; i++) cin >> end[i];

        Solution ob;
        int ans = ob.maxMeetings(start, end, n);
        cout << ans << endl;
    }
    return 0;
}  
