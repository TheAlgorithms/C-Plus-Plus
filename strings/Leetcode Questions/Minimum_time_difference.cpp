class Solution {
public:
    int findMinDifference(vector<string>& str) {
        

        vector<int> arr;
        for(int i = 0; i < str.size(); i++)
        {
            int hours = stoi(str[i].substr( 0 , 2));
            int mins  =stoi(str[i].substr( 3 , 5));

            int Totaltime = hours*60 + mins;

            arr.push_back(Totaltime);
        }

        sort(arr.begin() , arr.end());

        int minimum = INT_MAX;

        for(int i = 0; i < arr.size()-1; i++)
        {
           int mini = arr[i+1] - arr[i];
            minimum = min(mini , minimum);
        }

       int lastdiff = (arr[0] + 1440 ) - arr[arr.size()-1];

       minimum = min(minimum , lastdiff);

       return minimum;

    }
};
