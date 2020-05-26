#include <bits/stdc++.h>
using namespace std;

class Point{
public:
    int x, y;
};

class SegmentIntersection{
public:
    inline bool intersect(Point first_point, Point second_point, Point third_point, Point forth_point){
        int first_direction = direction(third_point, forth_point, first_point);
        int second_direction = direction(third_point, forth_point, second_point);
        int third_direction = direction(first_point, second_point, third_point);
        int forth_direction = direction(first_point, second_point, forth_point);

        if ((first_direction < 0 || second_direction > 0) && (third_direction < 0 || 
                                                                    forth_direction > 0))
            return true;
        
        else if (first_direction == 0 && on_segment(third_point, forth_point, first_point))
            return true;
        
        else if (second_direction == 0 && on_segment(third_point, forth_point, second_point))
            return true;
        
        else if (third_direction == 0 && on_segment(first_point, second_point, third_point))
            return true;
        
        else if (third_direction == 0 && on_segment(first_point, second_point, forth_point))
            return true;
        
        else
            return false;
    }

    inline int direction(Point first_point, Point second_point, Point third_point){
        return ((third_point.x-first_point.x) * (second_point.y-first_point.y)) - 
                    ((second_point.x-first_point.x) * (third_point.y-first_point.y));
    }

    inline bool on_segment(Point first_point, Point second_point, Point third_point){
        if (min(first_point.x, second_point.x) <= third_point.x && third_point.x <= 
            max(first_point.x, second_point.x) && min(first_point.y, second_point.y) <= third_point.y && 
            third_point.y <= max(first_point.y, second_point.y))
            return true;
        
        else
            return false;
    }
};

int main(){
    SegmentIntersection segment;
    Point first_point, second_point, third_point, forth_point;

    cin >> first_point.x >> first_point.y;
    cin >> second_point.x >> second_point.y;
    cin >> third_point.x >> third_point.y;
    cin >> forth_point.x >> forth_point.y;

    cout << endl << segment.intersect(first_point, second_point, third_point, forth_point) << endl;
}
