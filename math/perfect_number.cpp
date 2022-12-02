#include <iostream>

using namespace std;

void Check_Perfect_Number(int number, int i, int sum) {

  while (i < number) { // to check if the number itself is not less than 1 
    if (number % i == 0) // to take out factors 
      sum = sum + i; // adding the factors to the variable sum 
    i++;
  }

  if (sum == number) // 
    cout << i << " is a perfect number\n";
  else
    cout << i << " is not a perfect number\n";

}

int main() {

  cout << "\n\n------------To Check Wheather A Number Is Perfect Or Not---------------\n\n";

  /* 
  
  The logic behind to check if a number is perfect or not is 
  "If the sum of its factor is equal to the number itself, then the number is said to be perfect" 

  For example 6: The factors of 6 are 1,2,3 and since the sum of the factors 1+2+3==6 hence 6 is a perfect number 
  
  */

  int number, i = 1, sum = 0;
  char option;

  do { // To provide menu driven functionality to our code 

    cout << "Enter a number: ";
    cin >> number;

    Check_Perfect_Number(number, i, sum); // calling function to check perfectness of our number

    cout << "Do you wish to check another number ? Y/N "; // Y: Yes , N: No
    cin >> option;
    cout << endl;

    if (option == 'N') { // To break out from the code if the user does not want to enter another number

      cout << "EXIT !\n";
      break;

    }

  } while (option == 'Y'); // Running the code atleast once and till the user wants

  return 0;

}
