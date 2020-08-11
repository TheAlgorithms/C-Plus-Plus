// A Kaprekar number is a number whose 
// square when divided into two parts and such that 
// sum of parts is equal to the original number 
// and none of the parts has value 0.

//eg 45;  (45)^2 = 2025; 20 + 25 = 45
//eg 297; (297^2)2 = 88209 ; 88 + 209 = 297


#include<iostream>
#include<math.h>
using namespace std;
int karp(int no)
{
	int powr=0;
	long sq=no*no;
	while(sq)
	{
		powr++;
		sq=sq/10; // 
	}
	sq=no*no;
	for(int i=1;i<powr;i++)
	{
		int lim=pow(10,i);
		int kar=(sq/lim)+(sq%lim);
		if(kar==no||kar==1)
			return true;
	}
	return false;
}

int main()
{
	int no=0;
	cin>>no;
	if(karp(no))
	cout<<"karpekar";
	else
	cout<<"NOT karpekar";
		return 0;
}