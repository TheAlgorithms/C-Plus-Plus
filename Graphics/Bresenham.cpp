/* C++ program for Bresenham’s Line Generation 
   Assumptions : 
   1) Line is drawn from left to right. 
   2) x1 < x2 and y1 < y2 
   3) Slope of the line is between 0 and 1. We draw a line from lower left to upper right. */
#include<iostream,h>
#include<graphics.h>
 
//Function for drawing a line
void drawline(int x0, int y0, int x1, int y1)
{
    int dx, dy, p, x, y;
 
	//Difference between the points
	dx=x1-x0;
	dy=y1-y0;
 
	x=x0;
	y=y0;
 	
 	//Defining a P0 value
	p=2*dy-dx;
 
	//Consecutive points in range
	while(x<x1)
	{
		//While 
		if(p>=0)
		{
			putpixel(x,y,7);
			// Slope error reached limit, time to increment y and update slope error. 
			y=y+1;
			p=p+2*dy-2*dx;
		}
		else
		{
			putpixel(x,y,7);
			// Add slope to increment angle formed 
			p=p+2*dy;
		}
		x=x+1;
	}
}

//Driver Function
int main()
{
	//Variables for accessing graphics header file
	int gd=DETECT, gm; 
	initgraph(&gd, &gm, "c:\\tc\\bgi");
 
	int x0, y0, x1, y1;
	
	cout<<"Enter X co-ordinates of first point: ";
	cin>>x0;
	cout<<"Enter Y co-ordinates of first point: ";
	cin>>y0;
 
	cout<<"Enter co-ordinates of second point: ";
	cin>>x1;
	cout<<"Enter co-ordinates of second point: ";
	cin>>y1;
	
	drawline(x0, y0, x1, y1);
 
	return 0;
}