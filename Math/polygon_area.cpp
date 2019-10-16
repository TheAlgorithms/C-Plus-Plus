/*
 * This algorithm finds the area of a polygon
 * given as an array of vertices.
 *
 * i.e Let a polygon P be [[1,1], [2, 3], [4, 5]]
 * then the vertices of P are the elements of that array
 * and the edges of P are just Pi <-> Pi+1.
 *
 * The idea is to iterate through all the edges of P
 * and add the trapezoid areas bounded by each edge.
 * Area = Sum(edges in P) (((P[i].x - P[i+1].x) * (P[i].y - P[i+1].y)) / 2)
 *
 */

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

// We define a class that is the point.
class Point {
  public:
  double x;
  double y;

  Point(double x, double y) {
    this->x = x;
    this->y = y;
  }
};

// We define a polygon as a vector of points.
class Polygon {
  private:
  vector<Point> points;

  public:
  Polygon();
  Polygon(vector<Point> points) {
    this->points = points;
  }

  // Function that calculates the area
  double area() {
    double area = 0;
    int numPoints = this->points.size();

    for (int i = 0; i < numPoints; i++) {
      // We define an edge as Pi <-> Pi+1.
      // In case we're in the last point, the edge is from that point to the first one.
      Point p = this->points[i];
      Point q = this->points[(i + 1) % numPoints];
      area += (p.x - q.x) * (p.y + q.y);
    }

    return fabs(area) / 2;
  }
};


/*
 * Driver Program.
 * To double check your result, check
 * this website // visit this website https://www.mathopenref.com/coordpolygonareacalc.html
 */
int main() {
  // Define the points of the polygons
  Point a(1, 1),
        b(3, 5),
        c(6, 3);

  vector<Point> points;
  points.push_back(a);
  points.push_back(b);
  points.push_back(c);

  // Construct the polygon
  Polygon poly(points);

  // Print the area
  cout << poly.area() << endl;
}
