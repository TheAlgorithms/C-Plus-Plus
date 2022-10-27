#include <iostream>
using namespace std;
class prog2
{
    private:
    int a,b;
    public:
    prog2(int,int);
    prog2 operator + (prog2 &pg);
    prog2 operator - (prog2 &pg);
    void display();
    void display1();
    void display2();
};
prog2::prog2(int p=0,int q=0)
{
    a=p;
    b=q;
}
prog2 prog2::operator + (prog2 &pg1)
{
    prog2 pg;
    pg.a=a+pg1.a;
    pg.b=b+pg1.b;
    return pg;
}
prog2 prog2::operator - (prog2 &pg1)
{
    prog2 pg;
    pg.a=a-pg1.a;
    pg.b=b-pg1.b;
    return pg;
}
void prog2::display()
{
    if((a<0 && b<0)||(a>0 && b<0))
    cout<<"Addition: "<<a<<b<<"i\n";
    else
    cout<<"Addition: "<<a<<"+"<<b<<"i\n";
}
void prog2::display1()
{
    if((a<0 && b<0)||(a>0 && b<0))
    cout<<"Subtraction: "<<a<<b<<"i\n";
    else
    cout<<"Subtraction: "<<a<<"+"<<b<<"i\n";
}
int i=1;
void prog2::display2()
{
    if(i==1)
    {
        if((a<0 && b<0)||(a>0 && b<0))
        cout<<"First complex number is: "<<a<<b<<"i\n";
        else
        cout<<"First complex number is: "<<a<<"+"<<b<<"i\n";
        i++;
    }
    else
    {
        if((a<0 && b<0)||(a>0 && b<0))
        cout<<"Second complex number is: "<<a<<b<<"i\n";
        else
        cout<<"Second complex number is: "<<a<<"+"<<b<<"i\n";
    }
}
int main()
{
    int x,y;
    cout<<"Enter real part of the complex number: ";
    cin>>x;
    cout<<"Enter img part of the complex number: ";
    cin>>y;
    cout<<"\n";
    prog2 r(x,y);
    cout<<"Enter real part of the complex number: ";
    cin>>x;
    cout<<"Enter img part of the complex number: ";
    cin>>y;
    prog2 s(x,y);
    cout<<"\n";
    r.display2();
    s.display2();
    prog2 t=r+s;
    cout<<"\n";
    t.display();
    t=r-s;
    t.display1();
    return 0;
}
