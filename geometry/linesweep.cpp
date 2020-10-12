/**
 *  \addtogroup line sweep algorithm
 *  @{
 *  \file
 *  \brief Line sweep algorithm implementation
 *
 *  \author [Rudra Prasad Das](http://github.com/rudra697)
 *
 *  \details
 * It finds the minimum distance between 
 * n random given points
 *
 *  \example
 *  For points (1,3),(4,8),(9,5),(4,6),(7,1)
 * It returns the minimum distance 4.47214 units
 */
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cfloat>
/**
 * The class is created to store the x and y coordinates
 * 
 * **/
class Points
{
    public:
    int x,y; 
};
/**
 * The below two functions are comparators to be used
 * to guide the way the coordinates
 * are sorted
 * **/
bool cmpX(Points a,Points b)
{
    return a.x<b.x;
}
bool cmpY(Points a,Points b)
{
    return a.y<b.y;
}
/**
 * The following function calculates the minimum
 * distance between two closest point
 * int the n random given points
 * 
 * **/
double distance(Points p[],int si,int ei)
{
    /**
     * it is the base case and 
     * if it contains only two points 
     * it returns the distance between two points
     * **/
    if(ei-si==1)
    {
        return sqrt(pow(p[ei].x-p[si].x,2)+pow(p[ei].y-p[si].y,2));
    }
    /**
     * if it is a single point it returns the 
     * maximum possible point
     * **/
    if(ei-si<=0)
    {
        return DBL_MAX;
    }
    int mid=si+(ei-si)/2;
    /**
     * it partitions the random points
     * into two halves
     * **/
    return std::min(distance(p,si,mid),distance(p,mid+1,si));
}
/**
 * The following is the main function
 * It is the driving function
 * 
 * */
int main()
{
    int n;
    std::cin>>n;
    Points p[n];
    for(int i=0;i<n;i++)
    {
        int a,b;
        std::cin>>a>>b;
        p[i].x=a;
        p[i].y=b;
    }
    /**
     * it sorts on the x axis
     * **/
    std::sort(p,p+n,cmpX);
    int mid=n/2;
    double dl=distance(p,0,mid);
    double dr=distance(p,mid+1,n);
    /** calculating the minimum distance on the 
     * basis of x axis
     * **/
    double d=std::min(dl,dr);
    Points strip[n];
    int j=0;
    for(int i=0;i<n;i++)
    {
        if(abs(p[i].x-p[mid].x)<d)
        {
            strip[j++]=p[i];
        }
    }
    /** sorts on the basis
     * of y axis after calculating the 
     * strip
     * **/
    std::sort(strip,strip+j,cmpY);
    double ds=distance(strip,0,j);
    double ans=std::min(ds,d);
    std::cout<<ans<<"\n";

    


}