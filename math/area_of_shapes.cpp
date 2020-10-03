
#include <iostream>
#include <math.h>

float surface_area_cube(float side)
{
    if(side<0)
    {
        std::cout << "\n surface area only accept non-negative values";
    }
    else
    {
        return 6 * pow (side, 2);
    }
}

float surface_area_sphere(float radius)
{
    if(radius<0)
    {
        std::cout << "\n surface area only accept non-negative values";
    }
    else
    {
        return 4*M_PI*pow(radius,2);
    }
}

float area_rectangle(float length, float width)
{
    if(length<0 || width<0)
    {
        std::cout << "\n surface area only accept non-negative values";
    }
    else
    {
        return length*width;
    }
}

float area_square(float side)
{
    if(side<0)
    {
        std::cout << "\n surface area only accept non-negative values";
    }
    else
    {
        return pow(side,2);
    }
}

float area_triangle(float base, float height)
{
    if(base<0 || height<0)
    {
        std::cout << "\n surface area only accept non-negative values";
    }
    else
    {
        return (base * height) / 2.0;
    }
}

float area_parallelogram(float base, float height)
{
    if(base<0 || height<0)
    {
        std::cout << "\n surface area only accept non-negative values";
    }
    else
    {
        return (base * height);
    }
}

float area_trapezium(float base1 , float base2, float height)
{
    if(base1<0 || height<0 || base2<0)
    {
        std::cout << "\n surface area only accept non-negative values";
    }
    else
    {
        return (1 /2.0) * (base1 + base2) * height;
    }
}

float area_circle(float radius)
{
    if(radius<0)
    {
        std::cout << "\n surface area only accept non-negative values";
    }
    else
    {
        return M_PI*pow(radius,2);
    }
}

int main() {
    std::cout<<"the area of various geometric 2D shapes are";
    std::cout <<"\n Rectangle: "<<area_rectangle(10, 20);   //200
    std::cout <<"\n Square: "<<area_square(10);       //100
    std::cout <<"\n Triangle: "<<area_triangle(10, 10);   //50
    std::cout <<"\n Parallelogram: "<<area_parallelogram(10, 20);     //200
    std::cout <<"\n Trapezium: "<<area_trapezium(10, 20, 30);     //450
    std::cout <<"\n Circlel: "<<area_circle(20);        // 1256.64
    std::cout<<"\n the Surface area of various geometric 3D shapes are\n";
    std::cout <<"\n Cube: "<<surface_area_cube(20);   //2400
    std::cout <<"\n Sphere: "<<surface_area_sphere(20);     //5026.55
    return 0;
}
