//Author : Ayan Kumar Pahari

//included the required header file
#include <bits/stdc++.h>
using namespace std;

//Mergesort based on the y-coordinate of the points

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void MergeY(vector<pair<double, double>> &arr, int low, int mid, int high) //Merge function based on y-coordinate
{
    vector<pair<double, double>> temp;
    int i = low;
    int j = mid + 1;

    while (i <= mid && j <= high)
    {
        if (arr[i].second < arr[j].second) //comparing the y-coordinates of the points,the smaller one will come first
        {
            temp.push_back(arr[i++]);
        }
        else if (arr[i].second == arr[j].second && arr[i].first < arr[j].first) //in case the y-coordinates are same then the tie is broken based on the smaller x-coordinate
        {
            temp.push_back(arr[i++]);
        }
        else
        {
            temp.push_back(arr[j++]);
        }
    }

    while (i <= mid) //to push the left over points
    {
        temp.push_back(arr[i++]);
    }
    while (j <= high) //to push the left over points
    {
        temp.push_back(arr[j++]);
    }

    for (int i = low; i <= high; i++) //to write the array again in correct order
    {
        arr[i] = temp[i - low];
    }
}

void MergeSortY(vector<pair<double, double>> &arr, int low, int high) //Mergesort function based on y-coordinate
{
    if (low < high) //if low<high then only enter
    {
        int mid = (low + high) / 2;     //computing the middle value
        MergeSortY(arr, low, mid);      //left recursive call
        MergeSortY(arr, mid + 1, high); //right recursive call
        MergeY(arr, low, mid, high);    //merge procedure at the end
    }
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//Mergesort based on the x-coordinate of the points

void MergeX(vector<pair<double, double>> &arr, int low, int mid, int high) //Merge function based on x-coordinate
{
    vector<pair<double, double>> temp;
    int i = low;
    int j = mid + 1;

    while (i <= mid && j <= high)
    {
        if (arr[i].first < arr[j].first) //comparing the x-coordinates of the points,the smaller one will come first
        {
            temp.push_back(arr[i++]);
        }
        else if (arr[i].first == arr[j].first && arr[i].second < arr[j].second) //in case the x-coordinates are same then the tie is broken based on the smaller y-coordinate
        {
            temp.push_back(arr[i++]);
        }
        else
        {
            temp.push_back(arr[j++]);
        }
    }
    while (i <= mid) //to push the left over points
    {
        temp.push_back(arr[i++]);
    }
    while (j <= high)
    {
        temp.push_back(arr[j++]); //to push the left over elements
    }

    for (int i = low; i <= high; i++) //to write the array again in correct order
    {
        arr[i] = temp[i - low];
    }
}

void MergeSortX(vector<pair<double, double>> &arr, int low, int high)
{
    if (low < high) //if low<high then only enter
    {
        int mid = (low + high) / 2;     //computing the middle value
        MergeSortX(arr, low, mid);      //left recursive call
        MergeSortX(arr, mid + 1, high); //right recursive call
        MergeX(arr, low, mid, high);    //merge procedure at the end
    }
}

//the function find_distance() computes the distance between two pairs of points

double find_distance(pair<double, double> p1, pair<double, double> p2, pair<double, double> &min1, pair<double, double> &min2)
{
    //if new pair has shorter distance compared to the old pair of points, then update the closest pairs
    if (sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second)) < sqrt((min1.first - min2.first) * (min1.first - min2.first) + (min1.second - min2.second) * (min1.second - min2.second)))
    {
        min1 = p1;
        min2 = p2;
    }
    //returns the distance computed between the two points
    return sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}

//main function that computes the distance between the closest pair of points

double find_smallest_distance(vector<pair<double, double>> sorted_x, vector<pair<double, double>> sorted_y, pair<double, double> &min1, pair<double, double> &min2)
{

    int n = sorted_x.size(); //n contains the number of points

    if (n <= 1) //if n<=1 then no need to further divide
    {
        return DBL_MAX;
    }

    pair<double, double> p1, p2, p3, p4 = {DBL_MAX, DBL_MAX}; //initializing the dummy pairs as DBL_MAX
    vector<pair<double, double>> left_x;                      //left_x has the value when x-coordinate <=x_mid
    vector<pair<double, double>> right_x;                     //right_x has the value when x-coordinate > x_mid

    for (int i = 0; i < n; i++) //put the points in left_x and right_x
    {
        if (i < n / 2)
        {
            left_x.push_back(sorted_x[i]);
        }
        else
        {
            right_x.push_back(sorted_y[i]);
        }
    }
    int middle = left_x.back().first;             //compute the median value based on the x-coordinate
    vector<pair<double, double>> left_y, right_y; //Points in left_y have the value when y-coordinate <=x_mid and right_y contains the rest of the coordinates

    for (auto x : sorted_y) //fill the points in left_y and right_y
    {
        if (x.first <= middle)
        {
            left_y.push_back(x);
        }
        else
        {
            right_y.push_back(x);
        }
    }

    double d1 = find_smallest_distance(left_x, left_y, p1, p2);   //recursive call on the left region
    double d2 = find_smallest_distance(right_x, right_y, p3, p4); //recursive call on the right region

    if (d1 < d2) //update the closest points based on the minimum distance between them
    {
        min1 = p1;
        min2 = p2;
    }
    else
    {
        min1 = p3;
        min2 = p4;
    }

    double d = min(d1, d2); //d contains the minimum distance from both the regions

    vector<pair<double, double>> band; //band will contain all the elements that are distance d apart from the mid_x value in both direction

    for (auto x : sorted_y) //populating the band vector
    {
        if (x.first > middle - d)
            band.push_back(x);
    }

    for (int i = 0; i < band.size(); i++) //O(n) time loop
    {
        for (int j = i + 1; j < band.size() && band[j].second < band[i].second + d; j++) //this will take O(1) guaranteed, for each point it will check for it's neighbouring 7 points at max
        {
            if (find_distance(band[i], band[j], p1, p2) < d) //if found some better distance and points then simply update
            {
                min1 = band[i];
                min2 = band[j];
                d = find_distance(band[i], band[j], p1, p2);
            }
        }
    }

    return d; //return the closest distance found
}

int main()
{
    //initialization and taking the inputs
    //---------------------------------------------------------------------------------------------------------------------------------
    int n;                            //denotes the number of points
    vector<pair<double, double>> vec; //points will stored as a vector of pairs of double
    cout << "How many points are there on the 2D plane?  ";
    cin >> n;
    if (n <= 1) //check for any invalid conditions
    {
        cout << "Invalid Input" << endl;
        return 0;
    }

    for (int i = 1; i <= n; i++) //iterate n times and take the input points
    {
        double x, y;
        cout << "Enter the coordinates of Point " << i << endl;
        cout << "x" << i << ": ";
        cin >> x;
        cout << "y" << i << ": ";
        cin >> y;
        vec.push_back({x, y}); //push the coordinates into the vector
    }
    cout << endl;
    //----------------------------------------------------------------------------------------------------------------------------------
    //Sorted the points on the basics of x and y-coordinates in O(nlogn) time
    //----------------------------------------------------------------------------------------------------------------------------------
    MergeSortX(vec, 0, vec.size() - 1);          //Applying the merge sort on the x-coordinate of the points
    vector<pair<double, double>> sorted_x = vec; //sorted_x contains the points sorted on the basics of the x-coordinates

    MergeSortY(vec, 0, vec.size() - 1);          //Applying the merge sort on the y-coordinate of the points
    vector<pair<double, double>> sorted_y = vec; //sorted_y contains the points sorted on the basics of the y-coordinates
    //----------------------------------------------------------------------------------------------------------------------------------

    pair<double, double> min1 = {DBL_MAX, DBL_MAX}; //min1 and min2 contains the closest points found at the end
    pair<double, double> min2 = {DBL_MAX, DBL_MAX};

    double x = find_smallest_distance(sorted_x, sorted_y, min1, min2); //find_smallest_distance() function will return the smallest distance between two points

    //Shows the output
    //-----------------------------------------------------------------------------------------------------------------------------------
    cout << "The closest pair of points are (" << min1.first << "," << min1.second << ") "
         << "and "
         << "(" << min2.first << "," << min2.second << ") " << endl;
    cout << "The distance between them is " << x << " units" << endl;
    //------------------------------------------------------------------------------------------------------------------------------------
    return 0;
}