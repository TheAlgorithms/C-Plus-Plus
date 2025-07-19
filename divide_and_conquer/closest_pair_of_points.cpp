#include <bits/stdc++.h>
using namespace std;

// Structure to represent a 2D point
struct Point {
    int x, y;
};

// Function to compare points based on X coordinate
bool compareX(Point a, Point b) {
    return a.x < b.x;
}

// Function to compare points based on Y coordinate
bool compareY(Point a, Point b) {
    return a.y < b.y;
}

// Utility function to calculate Euclidean distance
double dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * 1.0 * (p1.x - p2.x) +
                (p1.y - p2.y) * 1.0 * (p1.y - p2.y));
}

// Brute force method for small number of points
double bruteForce(Point points[], int left, int right) {
    double minDist = DBL_MAX;
    for (int i = left; i < right; ++i) {
        for (int j = i + 1; j < right; ++j) {
            minDist = min(minDist, dist(points[i], points[j]));
        }
    }
    return minDist;
}

// Function to find the closest points in the strip
double stripClosest(vector<Point>& strip, double d) {
    double minDist = d;
    int n = strip.size();

    sort(strip.begin(), strip.end(), compareY);

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n && (strip[j].y - strip[i].y) < minDist; ++j)
            minDist = min(minDist, dist(strip[i], strip[j]));

    return minDist;
}

// Recursive function using Divide and Conquer
double closestUtil(Point points[], int left, int right) {
    if (right - left <= 3)
        return bruteForce(points, left, right);

    int mid = (left + right) / 2;
    Point midPoint = points[mid];

    double dl = closestUtil(points, left, mid);
    double dr = closestUtil(points, mid, right);

    double d = min(dl, dr);

    vector<Point> strip;
    for (int i = left; i < right; ++i) {
        if (abs(points[i].x - midPoint.x) < d)
            strip.push_back(points[i]);
    }

    return min(d, stripClosest(strip, d));
}

// Main function to be called
double closestPair(Point points[], int n) {
    sort(points, points + n, compareX);
    return closestUtil(points, 0, n);
}

// --------- Sample Driver Code ---------
int main() {
    Point points[] = {{2, 3}, {12, 30}, {40, 50},
                      {5, 1}, {12, 10}, {3, 4}};
    int n = sizeof(points) / sizeof(points[0]);

    cout << fixed << setprecision(4);
    cout << "The smallest distance is " << closestPair(points, n) << endl;

    return 0;
}
