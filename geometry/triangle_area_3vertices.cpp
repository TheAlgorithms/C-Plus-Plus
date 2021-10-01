// Compute area of triangle given it's vertices

#include<iostream>
#include<cmath>
#include<iomanip>

double eps = 1e-9;

struct Point{
    // Data members: x, y co-ordinates of the point
    // Member functions: dist (To find distance to some other Point object)
    double x;
    double y;
    Point(){
        std::cin>>x;
        std::cin>>y;
    }
    Point(double x1,double y1): x(x1),y(y1){};
    double dist(Point a){
        double delta_x = x-a.x;
        double delta_y = y-a.y;
        return sqrt(delta_x*delta_x+delta_y*delta_y);
    }
};

double heron_area(Point a,Point b,Point c){
    // herons formula : s(s-a)(s-b)(s-c) = area**2
    // a small eps is added to avoid double precision errors when the points are collinear
    double ab = a.dist(b);
    double bc = b.dist(c);
    double ca = c.dist(a);
    double s = (ab+bc+ca)/2+eps;
    return sqrt(s*(s-ab)*(s-bc)*(s-ca));
}

int main(){
    std::cout<<std::setprecision(3)<<'\n';
    Point a,b,c;
    std::cout<<heron_area(a,b,c)<<'\n';
}