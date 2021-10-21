#include <iostream>
#include<bits/stdc++.h>
using namespace std;

void check_bit(int num, int pos){
    /*
    To check weather the given bit value is set or not.
    example: num=5, position=3 (answer: set-bit)
    returns: weather its a set-bit or unset-bit.
    */
    if(num&(1<<(pos-1)))
        cout<<"set-bit";
    else
        cout<<"unset-bit";
}
void set_the_bit(int num, int pos){
    /*
    To set the particular bit
    example: num=5, position=2 
    returns: "unset_bit" 
            because the bit value is 0.
    */
    int x, res;
    x=1<<(pos-1);
    res=num^x;
    cout<<"Setted the bit value as: "<<res;
}
int set_bit_count(int num){
    /*
    To count the number of setbits in the given number.
    example: num=5(Binary number is 0101)
    returns: the count of setbits. 
    */
	int count=0;
	while(num)
	{
		if(num&1==1){
			count++;
		}
		num = num>>1; 
	}
	cout<<"The no. of setbits = "<<count;
	return count;
}
void unset_the_bit(int num, int pos){
    /*
    To unset the particular bit.
    example: num=5, position=3
    returns: position value to unset-bit and gives the number
    */
    int x = 1<<pos-1;
    cout<<"Unsetted the bit and the number is: "<<(num|x);
}
int main()
{
    int num, pos;
    cin>>num>>pos;
    check_bit(num, pos);
    cout<<"\n";
    set_the_bit(num, pos);
    cout<<"\n";
    set_bit_count(num);
    cout<<"\n";
    unset_the_bit(num, pos);
    cout<<"\n";
    return 0;
}
