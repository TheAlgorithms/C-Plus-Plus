#include<iostream>  
using namespace std;
class Rev
{
	private:
		int n,i;
	public:
		Rev()
		{
			cout<<"Enter Number to Display reverse: ";
			cin>>n;
		}
		friend void show(Rev);
};
void show(Rev r)
{
	 cout<<"The reverse the Entered number: ";
	 for(r.i=r.n;r.i>0;r.i=r.i/10){
	  	cout<<r.i%10;
	}
}
int main()
{
    Rev r;
    show(r);
    return 0;
}
