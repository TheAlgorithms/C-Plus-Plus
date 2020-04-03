#include<iostream>

using namespace std;

int main(){
	int year = 1; // Starting from 1901
	int monthNotLeap[] = {31,28,31,30,31,30,31,31,30,31,30,31}; // duration of months in a non-leap year.
	int monthLeap[] = {31,29,31,30,31,30,31,31,30,31,30,31}; // duration of months in a leap year.
	int shift = 0; // Used for making a shift in starting point/day of a given month
	int answer = 0;
	
	for(year = 1; year <=100; ++year){
		if(year%4 == 0){ // If the year is a leap year
			shift += 2; // Because in a leap year there are 366 days and 366 % 7 == 2
			if(shift > 6)
				shift = shift % 7; // better for computation (maybe) !! CHECK LATER
			for(int i = 0; i<12; ++i){ //iterating over the months in the year
				if((monthLeap[i] + shift) % 7 == 5){ 	// because the 1 Jan 1901 was a Tuesday therefore Tuesday = 0, Wednesday = 1, ... Sunday = 5, Monday = 6
					++answer;
				}
			}
		} else {
			shift += 1; // Because in a non-leap year there are 365 days and 365 % 7 == 1
			if(shift > 6)	
				shift = shift % 7;
			for(int i=0; i<12; ++i){ //Iterating again over months (probably should create a function for this)
				if((monthNotLeap[i]	+ shift) % 7 == 5){
					++answer;
				}
			}
		}
	}
	
	cout<<"Answer is "<< answer << "\n";
	return 0;
}

