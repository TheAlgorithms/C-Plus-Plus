

#include <iostream>
#include <math.h>
using namespace std;
float vol_cube(float side)
{
    float vol;
    vol=side*side*side;
    return vol;
}

float vol_cuboid(float bredth,float length,float height)
{
    float vol;
    vol=bredth*length*height;
    return vol;
}

float vol_cone(float area_of_base,float height)
{
    float vol;
    vol=area_of_base*height*(1/3.0);
    return vol;
}

float vol_right_circ_cone(float radious,float height)
{
    float vol;
    vol=M_PI*radious*radious*height*(1/3.0);
    return vol;
}

float vol_prism(float area_of_base,float height)
{
    float vol;
    vol=area_of_base*height;
    return vol;
}

float vol_pyramid(float area_of_base,float height)
{
    float vol;
    vol=area_of_base*height/3.0;
    return vol;
}

float vol_sphere(float radius)
{
    float vol;
    vol=(4/3.0)*M_PI*pow(radius,3);
    return vol;
}

float vol_circular_cylinder(float radius,float height)
{
    float vol;
    vol=M_PI * pow(radius, 2) * height;
    return vol;
}

int main() {
    
    std::cout<<"the volume of different Volume structure \n";
    std::cout<<"\nCube: "<<vol_cube(2.0);
    std::cout<<"\nCuboid: "<<vol_cuboid(2, 2, 2);
    std::cout<<"\nCone: "<<vol_cone(2, 2);
    std::cout<<"\nRight Circular Cone: "<<vol_right_circ_cone(2, 2);
    std::cout<<"\nPrism: "<<vol_prism(2, 2);
    std::cout<<"\nPyramid: "<<vol_pyramid(2, 2);
    std::cout<<"\nSphere: "<<vol_sphere(2);
    std::cout<<"\nCircular Cylinder: "<<vol_circular_cylinder(2, 2);
    
    return 0;
}
