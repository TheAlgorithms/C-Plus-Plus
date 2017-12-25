#include <iostream>

using namespace std;

void main(void)
{
	int valueToConvert = 0; //Holds user input
	int hexArray[8];       //Contains hex values backwards
	int i = 0;             //counter
	int lValue = 0;       //Last Value of Hex result

	cout << "Enter a Decimal Value" << endl; //Displays request to stdout
	cin >> valueToConvert;					        //Stores value into valueToConvert via user input

	while (valueToConvert > 0)        //Dec to Hex Algorithm
	{
		lValue = valueToConvert % 16;        //Gets remainder
		valueToConvert = valueToConvert / 16;
		hexArray[i] = lValue;             //Stores converted values into an array
		i++;
	}
	cout << "Hex Value: ";
	while (i > 0)
	{
		//Displays Hex Letters to stdout
		switch (hexArray[i - 1]) {
			case 10:
				cout << "A"; 
				break;
			case 11:
				cout << "B";
				break;
			case 12:
				cout << "C";
				break;
			case 13:
				cout << "D";
				break;
			case 14: 
				cout << "E";
				break;
			case 15:
				cout << "F";
				break;
			default:
				cout << hexArray[i - 1]; //if not an int 10 - 15, displays int value
		}
			i--;
	}
	cout << endl;
}
