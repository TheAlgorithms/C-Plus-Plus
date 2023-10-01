#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>

using namespace std;

// Data structure to represent a point in 2D space
struct Point {
    double x, y;

    // Constructor to initialize a point
    Point(double x, double y) : x(x), y(y) {}
};

// Data structure to represent an edge between two points
struct Edge {
    int u, v;
    double weight;

    // Constructor to initialize an edge
    Edge(int u, int v, double weight) : u(u), v(v), weight(weight) {}
};

// Function to calculate the Euclidean distance between two points
double euclideanDistance(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

// Function to find the closest pair of points in a given range
Edge closestPair(vector<Point>& points, int left, int right) {
    if (right - left <= 1) {
        // Base case: if there are only two points, return the edge between them
        return Edge(left, right, euclideanDistance(points[left], points[right]));
    }

    // Divide the range into two halves
    int mid = (left + right) / 2;
    double midX = points[mid].x;

    // Recursively find the closest pair in the left and right halves
    Edge leftClosest = closestPair(points, left, mid);
    Edge rightClosest = closestPair(points, mid + 1, right);

    // Find the minimum of the two closest pairs
    Edge minClosest = (leftClosest.weight < rightClosest.weight) ? leftClosest : rightClosest;

    // Create a vector to store points in the strip of width 2*minClosest.weight
    vector<Point> strip;

    // Populate the strip with points whose x-coordinate is within the strip
    for (int i = left; i <= right; i++) {
        if (abs(points[i].x - midX) < minClosest.weight) {
            strip.push_back(points[i]);
        }
    }

    // Sort the points in the strip by their y-coordinates
    sort(strip.begin(), strip.end(), [](const Point& p1, const Point& p2) {
        return p1.y < p2.y;
    });

    // Iterate through the strip to find potential closer pairs
    for (int i = 0; i < strip.size(); i++) {
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minClosest.weight; j++) {
            double distance = euclideanDistance(strip[i], strip[j]);
            if (distance < minClosest.weight) {
                minClosest = Edge(left + i, left + j, distance);
            }
        }
    }

    return minClosest;
}

int main() {
    int n; // Number of points
    cout << "Enter the number of points: ";
    cin >> n;
    cin.ignore(); // Consume the newline character

    vector<Point> points;
    cout << "Enter the coordinates of each point (comma-separated):" << endl;
    
    // Read the coordinates as a single comma-separated string
    string coordinates;
    getline(cin, coordinates);

    // Use a stringstream to parse the coordinates
    stringstream ss(coordinates);
    for (int i = 0; i < n; i++) {
        double x, y;
        char comma;
        ss >> x >> comma >> y;
        points.push_back(Point(x, y));
    }

    // Sort the points by their x-coordinates
    sort(points.begin(), points.end(), [](const Point& p1, const Point& p2) {
        return p1.x < p2.x;
    });

    // Find the closest pair of points using Chazelle's Algorithm
    Edge closest = closestPair(points, 0, n - 1);

    cout << "Closest pair of points: (" << points[closest.u].x << ", " << points[closest.u].y << ") and ("
         << points[closest.v].x << ", " << points[closest.v].y << ")" << endl;
    cout << "Distance between them: " << closest.weight << endl;

    return 0;
}
