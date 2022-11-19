# include <iostream>
# include <graphics.h>
# include <math.h>
using namespace std;

class Line 
{
	float x1,x2,y1,y2;
	float length;
	float Dx, Dy;
	int x,y;
	
	
	public:
		
		Line(){
			//code
		}
		
		Line ( float a, float b, float c, float d ) 
		{	
			this->x1 = a;
			this->y1 = b;
			this->x2 = c;
			this->y2 = d;
			
			cout << "Processed co-ordinates successfully" << endl;
		}
		
		void printCords () 
		{	
			cout << "Start Point ("<<x1<<","<<y1<<")\n";
			cout << "End Point ("<<x2<<","<<y2<<")\n";
		}
		
		void dda(int);
		
};

void Line::dda(int color) 
		{
			if ( abs(x2-x1) >= abs(y2-y1))
				length = abs (x2-x1);
			else
				length = abs (y2-y1);
			
			Dx = (x2-x1)/length;
			Dy = (y2-y1)/length;
			
			x = x1;
			y = y1;
			
			int i = 0;
			
			while ( i<= length )
			{
				putpixel(floor(x),floor(y),color);
				
				x += Dx;
				y += Dy;
				i++;
			}
		}
int main()
{
	int gd, gm;
	gd = DETECT;
	initgraph(&gd,&gm,NULL);
	
	Line L(50,50,235,235);
	L.dda(12);
	delay(100000);

	getch();
	
	closegraph();
	cout << "END" << endl;
}
