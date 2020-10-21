#include<iostream>
using namespace std;
int main()
{
	int a[8]={23,45,12,67,34,89,1,33};
	int i,key;
	bool flag=false;
	cout<<"enter key vakue";
	cin>>key;
	for(i=0;i<8;i++)
		if(a[i]==key)
		{
			flag=true;
			break;	
		}
	
	if(flag==true)
		cout<<"element found at "<<i+1<<"position"<<endl;
	else
		cout<<"not found"<<endl;
	
}
