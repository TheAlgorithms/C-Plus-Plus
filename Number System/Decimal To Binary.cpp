#include<iostream>
using namespace std;
int main()
{
	int number;
	cin>>number;
	int remainder,binary=0,var=1;

do{
		
	 remainder=number%2;
	number=number/2;
	binary=binary+(remainder*var);
	var=var*10;


}
while(number>0);
	cout<<binary;
}
