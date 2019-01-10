#include<iostream>
using namespace std;

// To pad both input strings with 0's so they have same size
int equalLength(string &bitStr1, string &bitStr2)
{
	int strLen1 = bitStr1.size();
	int strLen2 = bitStr2.size();

	if(strLen1>strLen2){
		int numZerosToPad = strLen1 - strLen2;
		for(int i=0; i< numZerosToPad; i++)
			bitStr2 = '0' + bitStr2;
	}

	else if(strLen2>strLen1){
		int numZerosToPad = strLen2 - strLen1;
		for(int i=0; i< numZerosToPad; i++)
			bitStr1 = '0' + bitStr1;
	}

	return max(strLen1, strLen2);
}

string addBitStrings(string bitStr1, string bitStr2)
{
    string result="";
    int len = equalLength(bitStr1, bitStr2);

    // For first bit addition carry is 0
    int carry = 0;
    for(int i=len-1; i>=0; i--){
		// We need to convert '0' or '1' to 0 or 1. Subtracting '0' from the character, subtracts
		// their ascii values which results in 0 or 1.
		int bit1 = bitStr1.at(i) - '0';
		int bit2 = bitStr2.at(i) - '0';

		// XOR to add the bits and the previous carry
		// Adding '0' so that 0 or 1 can be cast to '0' or '1'
		char sum = (char)((bit1 ^ bit2 ^ carry) + '0');
		result = sum + result;

		// Boolean expression for carry(full adder carry expression)
		carry = (bit1&bit2) | (bit2&carry) | (bit1&carry);

	}

	  // if overflow, then add a leading 1 
    if (carry)  
    	result = '1' + result; 
    return result;
}

long long int karatsubaMultiply(string x, string y)
{
    int n = equalLength(x, y);

	//Recursion base cases(when length of the bit string is 0 or 1)
    if (n == 0) return 0; 
    if (n == 1){
    	// Single bit multiplication. 
    	return (x[0] - '0')*(y[0] - '0');
    }

    int firstHalfLen = n/2;    
    int secondHalfLen = (n-firstHalfLen);
    string Xleft = x.substr(0, firstHalfLen);
    string Xright = x.substr(firstHalfLen, secondHalfLen);

    string Yleft = y.substr(0, firstHalfLen);
    string Yright = y.substr(firstHalfLen, secondHalfLen);

    long long int product1 = karatsubaMultiply(Xleft, Yleft);
    long long int product2 = karatsubaMultiply(Xright, Yright);
    long long int product3 = karatsubaMultiply(addBitStrings(Xleft, Xright), 
    										   addBitStrings(Yleft, Yright));

    return product1*(1<<(2*secondHalfLen)) +
           (product3 - product1 - product2) * (1<<secondHalfLen) + product2;
}

int main()
{
    cout<<"Product of 1011 and 110 = "<<karatsubaMultiply("1011", "110")<<endl;
    cout<<"Product of 1111 and 0 = "<<karatsubaMultiply("1111", "0")<<endl;
    cout<<"Product of 100000 and 10 = "<<karatsubaMultiply("100000", "10")<<endl;
    cout<<"Product of 101 and 101101 = "<<karatsubaMultiply("101", "101101")<<endl;
}