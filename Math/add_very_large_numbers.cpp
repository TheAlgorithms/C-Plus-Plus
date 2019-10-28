#include<iostream>
#include<stdlib.h>
#include<string.h>

#define MAXLEN 800
#define MAX(a,b) (a>b)?a:b;

int main()
{
	char *a, *b, *c, *ip1, *ip2;
	int x1,x2,sum,car,full,len;

	ip1 = new char[MAXLEN];
	ip2 = new char[MAXLEN];
	std::cin>>ip1;
	std::cin>>ip2;

	len = MAX(strlen(ip1), strlen(ip2));
	a = new char[len];
	b = new char[len];
	memset(a,'0',len);
	memset(b,'0',len);

	for(int i=len-strlen(ip1),j=0; i<len, j<strlen(ip1); i++,j++)
		a[i] = ip1[j];

	for(int i=len-strlen(ip2),j=0; i<len, j<strlen(ip2); i++,j++)
		b[i] = ip2[j];

	delete ip1;
	delete ip2;

	c = new char[len+1];
	memset(c,'0',len+1);

	car = 0;
	for(int i=len-1;i>=0;i--)
	{
		x1 = a[i] - '0';
		x2 = b[i] - '0';
		full = x1+x2+car;
		sum = full%10;
		car = full/10;
		c[i+1] = sum + '0';
	}
	c[0] = car + '0';
	std::cout<<c<<std::endl;

	delete a;
	delete b;
	delete c;

}
