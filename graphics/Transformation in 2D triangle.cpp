#include<iostream>
#include<graphics.h>
#include<math.h>

using namespace std;
main(){
	char choice;
	int gd= DETECT, gm;
	int x1,y1,x2,y2,x3,y3;
    initgraph(&gd, &gm, "");
    // Entering coordinates of the triangle
    cout <<"Enter first coordinates of triangle:"<< endl;
    cin>>x1>>y1;
    cout<<"Enter second coordinates of triangle:"<< endl;
    cin>>x2>>y2;
    cout<<"Enter third coordinates of triangle:"<< endl;
    cin>>x3>>y3;
    // Printing the lines 
    line(x1,y1,x2,y2);
    line(x2,y2,x3,y3);
    line(x3,y3,x1,y1);


do
{
	cout<<endl;
	cout<<"Transformations"<<endl;
	cout<<"1. Translation"<<endl;
	cout<<"2. Rotation"<<endl;
	cout<<"3. Shearing"<<endl;
	cout<<"4. Scaling"<<endl;
	cout<<"5. Exit"<<endl;
	
	cout<<"Enter your choice: "<<endl;
	cin>>choice;

	switch(choice)
	{
    // Translation in 2D Triangle
		case '1':
			int tx, ty;
			cout<<"Enter tanslation vector: "<<endl;
    		cin>>tx>>ty;
    		setcolor(RED);
  			line(x1+tx, y1+ty, x2+tx, y2+ty);
  			line(x2+tx, y2+ty, x3+tx, y3+ty);
  			line(x3+tx, y3+ty, x1+tx, y1+ty);
  			getch();
  			closegraph();
			break;
		
    // Rotaion in 2D Triangle
		case '2':
			int x,y,a1,b1,a2,b2,a3,b3;
    		float Angle;
		    cout<<"Enter the angle for rotation:"<<endl;
		    cin >> Angle;
		    Angle=(Angle*3.14)/180;
		    a1=x2+(x1-x2)*cos(Angle)-(y1-y2)*sin(Angle);
		    b1=y2+(x1-x2)*sin(Angle)+(y1-y2)*cos(Angle);
		    a2=x2+(x2-x2)*cos(Angle)-(y2-y2)*sin(Angle);
		    b2=y2+(x2-x2)*sin(Angle)+(y2-y2)*cos(Angle);
		    a3=x2+(x3-x2)*cos(Angle)-(y3-y2)*sin(Angle);
		    b3=y2+(x3-x2)*sin(Angle)+(y3-y2)*cos(Angle);
		    setcolor(YELLOW);
  			line(a1, b1, a2, b2);
  			line(a2, b2, a3, b3);
  			line(a3, b3, a1, b1);
  			getch();
  			closegraph();
			break;
		
    // Scaling in 2D Triangle
		case '3':
			int sh;
			cout<<"Enter scaling factor: "<<endl;
    		cin>>sh;
    		x1 = x1 + y1*sh;
    		x2 = x2 + y2*sh;
    		x3 = x3 + y3*sh;
    		setcolor(GREEN);
  			line(x1, y1, x2, y2);
  			line(x2, y2, x3, y3);
  			line(x3, y3, x1, y1);
  			getch();
  			closegraph();
			break;
		
    // Shearing in 2D Triangle
		case '4':
			int sx, sy;
			cout<<"Enter scaling factor: "<<endl;
    		cin>>sx>>sy;
    		x1 = x1 * sx;
    		x2 = x2 * sx;
    		x3 = x3 * sx;
    		y1 = y1 * sy;
    		y2 = y2 * sy;
    		y3 = y3 * sy;
    		setcolor(RED);
  			line(x1, y1, x2, y2);
  			line(x2, y2, x3, y3);
  			line(x3, y3, x1, y1);
  			getch();
  			closegraph();
			break;
				
		case '5':
            exit(0);
				
		default:   cout<<"Wrong choice...!!"<< endl;		   
	               break;
	    
	}
}
while(choice!=5 && choice!= getchar());		  

}



/*
EXAMPLE INPUT
Enter first coordinates of triangle: 50 150
Enter second coordinates of triangle: 150 200
Enter third coordinates of triangle: 250 300

Translation Vector: 100 100
Angle of rotaion: 30
Shearing Factor: 2
Scaling Factor: 2 2
*/


