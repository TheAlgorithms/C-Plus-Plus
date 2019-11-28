#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct Point
{
    double x, y;
    Point(double a = 0.0, double b = 0.0)
    {
        x = a;
        y = b;
    }
};

double LenghtLine(Point A, Point B)
{
    return sqrt(abs((B.x - A.x) * (B.x - A.x)) + abs((B.y - A.y) * (B.y - A.y)));
}

double TriangleArea(Point A, Point B, Point C)
{
    double a = LenghtLine(A, B);
    double b = LenghtLine(B, C);
    double c = LenghtLine(C, A);
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

bool PointInCircle(vector<Point> &P, Point Center, double R)
{
    for (size_t i = 0; i < P.size(); i++)
    {
        if (LenghtLine(P[i], Center) > R)
            return false;
    }
    return true;
}

double circle(vector<Point> P)
{
    double minR = INT8_MAX;
    double R;
    Point C;
    Point minC;
    for (size_t i = 0; i < P.size() - 2; i++)
        for (size_t j = i + 1; j < P.size(); j++)
            for (size_t k = j + 1; k < P.size(); k++)
            {
                C.x = -0.5 * ((P[i].y * (P[j].x * P[j].x + P[j].y * P[j].y - P[k].x * P[k].x - P[k].y * P[k].y) + P[j].y * (P[k].x * P[k].x + P[k].y * P[k].y - P[i].x * P[i].x - P[i].y * P[i].y) + P[k].y * (P[i].x * P[i].x + P[i].y * P[i].y - P[j].x * P[j].x - P[j].y * P[j].y)) / (P[i].x * (P[j].y - P[k].y) + P[j].x * (P[k].y - P[i].y) + P[k].x * (P[i].y - P[j].y)));
                C.y = 0.5 * ((P[i].x * (P[j].x * P[j].x + P[j].y * P[j].y - P[k].x * P[k].x - P[k].y * P[k].y) + P[j].x * (P[k].x * P[k].x + P[k].y * P[k].y - P[i].x * P[i].x - P[i].y * P[i].y) + P[k].x * (P[i].x * P[i].x + P[i].y * P[i].y - P[j].x * P[j].x - P[j].y * P[j].y)) / (P[i].x * (P[j].y - P[k].y) + P[j].x * (P[k].y - P[i].y) + P[k].x * (P[i].y - P[j].y)));
                R = (LenghtLine(P[i], P[j]) * LenghtLine(P[j], P[k]) * LenghtLine(P[k], P[i])) / (4 * TriangleArea(P[i], P[j], P[k]));
                if (!PointInCircle(P, C, R))
                {
                    continue;
                }
                if (R <= minR)
                {
                    minR = R;
                    minC = C;
                }
            }
    for (size_t i = 0; i < P.size() - 1; i++)
        for (size_t j = i + 1; j < P.size(); j++)
        {
            C.x = (P[i].x + P[j].x) / 2;
            C.y = (P[i].y + P[j].y) / 2;
            R = LenghtLine(C, P[i]);
            if (!PointInCircle(P, C, R))
            {
                continue;
            }
            if (R <= minR)
            {
                minR = R;
                minC = C;
            }
        }
    cout << minC.x << " " << minC.y << endl;
    return minR;
}

void test()
{
    vector<Point> Pv(5);
    Pv.push_back(Point(0, 0));
    Pv.push_back(Point(1, 3));
    Pv.push_back(Point(4, 1));
    Pv.push_back(Point(5, 4));
    Pv.push_back(Point(3, -2));
    cout << circle(Pv) << endl;
}

void test2()
{
    vector<Point> Pv(4);
    Pv.push_back(Point(0, 0));
    Pv.push_back(Point(0, 2));
    Pv.push_back(Point(2, 2));
    Pv.push_back(Point(2, 0));
    cout << circle(Pv) << endl;
}

void test3()
{
    vector<Point> Pv(3);
    Pv.push_back(Point(0.5, 1));
    Pv.push_back(Point(3.5, 3));
    Pv.push_back(Point(2.5, 0));
    cout << circle(Pv) << endl;
}
int main()
{
    test();
    cout << endl;
    test2();
    cout << endl;
    test3();
    return 0;
}
