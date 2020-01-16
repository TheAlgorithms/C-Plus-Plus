#include <iostream>

using namespace std;

int main(void)
{
	int valueToConvert = 0; //Holds user input
	int hexArray[8];		//Contains hex values backwards
	int i = 0;				//counter
	char HexValues[] = "0123456789ABCDEF";

	cout << "Enter a Decimal Value" << endl; //Displays request to stdout
	cin >> valueToConvert;					 //Stores value into valueToConvert via user input

	while (valueToConvert > 15)
	{										 //Dec to Hex Algorithm
		hexArray[i++] = valueToConvert % 16; //Gets remainder
		valueToConvert /= 16;
	}
	hexArray[i] = valueToConvert; //Gets last value

	cout << "Hex Value: ";
	while (i >= 0)
		cout << HexValues[hexArray[i--]];

	cout << endl;
	return 0;
}
