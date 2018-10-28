#include<iostream>
using namespace std;


  int main()
   {
    int side1,side2,option,flag=0;
    float area=0;
    while(!flag)
    {
     system("cls");
     cout<<"\n********FIND THE AREA********\n\n";
     cout<<"Enter the shape\n";
     cout<<"1.Circle\n2.Square\n3.Rectangle\n4.Exit\n";
     cout<<"Choice :";
     cin>>option;

     switch(option)
      {
       //circle
       case 1:cout<<"Enter the radius of the circle in centimeters\n";
	      cin>>side1;
	      area=3.14*side1*side1;
	      cout<<"The area of the circle = "<<area<<endl;
	      system("pause");
	      break;
       //square
       case 2:cout<<"Enter the side of the square in centimeters\n";
	      cin>>side1;
	      area=side1*side1;
	      cout<<"The area of the square = "<<area<<endl;
	      system("pause");
	      break;
       //rectangle
       case 3:cout<<"Enter the length and breadth of the rectangle in centimeters\n";
	      cin>>side1>>side2;
	      area=side1*side2;
	      cout<<"The area of the rectangle ="<<area<<endl;
	      system("pause");
	      break;
       case 4:exit (0);
        break;
       //unspecified shape
       default:cout<<"Invalid Operator\n";
           system("pause");
	       break;
      }
    }
   return 0;
  }
