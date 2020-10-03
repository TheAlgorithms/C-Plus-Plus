#include<bits/stdc++.h>
#include<gl/glut.h>
#include <cmath>
using namespace std;

void init()
{
 glClearColor(0,0,0,0);
 glMatrixMode(GL_PROJECTION);
 glOrtho(-100,100,-100,100,20,-20);
}


const float v[5][3] = {     {0.8,0.5,0.0} ,
                            {0.0,0.5,0.9} ,
                            {0.5,0.0,0.9} ,
                            {0.8,0.0,0.3} ,
                            {0.8,0.8,0.3}   };


// 5 color values to code each bar with a different color

int value[5];



// To create the grid for the histogram

void grid()
{
     glBegin(GL_LINES);
     glColor3f(1.0,1.0,1.0);


     glVertex2f(-90,-90);
     glVertex2f(90,-90);

     glVertex2f(-90,-90);
     glVertex2f(-90,90);

     glEnd();



}


// To print the histogram graphically

void histogram(int ya, int yb, int xa, int xb , int i)
{
    glBegin(GL_LINES);
     glColor3f(v[i][0],v[i][1],v[i][2]);

     for(int i=ya;i<=yb; i=i+2)
     {
         glVertex2f(i,xb);
         glVertex2f(i,xa);
     }

     for(int i=xb;i>xa;i=i-2)
     {
         glVertex2f(ya,i);
         glVertex2f(yb,i);
     }
     glEnd();
}




// To make the grid of histogram and call the function 
// to print the histogram graphically
void display()
{
  glClear(GL_COLOR_BUFFER_BIT);



    //histogram(-70,-50,-90,70);
    int i=0;
    for(int x = -70; x<=50; x+=30)
    {
        histogram(x,(x+20),-90,value[i], i);
        i++;
    }
    grid();



    glColor3f(1.0,1.0,1.0);
     glRasterPos2f(0,0);
     //glutStrokeCharacter(GLUT_STROKE_ROMAN, 'HELLO');
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'20');

  glFlush();
}





// Main function to take inputs and run the display() function
// The main function takes in 5 inputs as percentages 
// It then displays the relativistic histogram among the values

int main(int argc,char **argv)
{
    cout<<"Enter the percentage value for 5 entities under consideration"<<endl;
    for(int i=0;i<5;i++)
    {
        std::cin>>value[i];
        value[i] = 1.8*value[i] -90;
    }

 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_RGB);
 glutInitWindowSize(500,500);
 glutInitWindowPosition(800,100);
 glutCreateWindow("Shashwat Kumar");
 init();
 glutDisplayFunc(display);
 glutMainLoop();
}

