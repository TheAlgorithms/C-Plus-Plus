#include <iostream>
#include <math.h>
float hypotenuse(float x,float y)   //where x and y are the two side of right angle triangle
{
    if(x<0 || y<0)
    {
        std::cout<<"the side must be non-negative number ";
        return 0;
    }
    else
    {
        return sqrt(pow(x,2)+pow(y,2));
    }
}
int main() {
    float side1,side2; //side 1 and side 2 are perpendicular adjesent sides of right angle triangle
    side1=3;
    side2=4;
    std::cout<<"the hypotenuse of the triangle of sides "<<side1<<" and "<<side2<<" is = "<<hypotenuse(side1,side2);
    return 0;
}
