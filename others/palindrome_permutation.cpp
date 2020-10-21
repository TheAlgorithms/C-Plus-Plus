#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;

bool is_palindrome(string);

int main(int argc, char *argv[]) {

  string input;
  string tempstring; // temporary string used to remove all spaces, punctuation, etc.
  unsigned int len; // holds the size of the temporary string
  bool valid; // used to determine if the word is a valid palindrome permutation

  cout << "Enter string: ";
  cin >> input;

	valid = false;
	tempstring = input;

	len = tempstring.size();

  tempstring.erase(remove(tempstring.begin(), tempstring.end(), ' '), tempstring.end()); // erases all spaces in the string

	for(unsigned int i = 0; i < len; i++){

		if(ispunct(tempstring[i])){ // if there is a punctuation, it will be removed

			tempstring.erase(i--, 1);
			len = tempstring.size();
		}
		else if(isupper(tempstring[i])){ // if there is an upper case letter, it will be converted to lower case

			tempstring[i] = tolower(tempstring[i]);
		}
	}
  valid = is_palindrome(tempstring);

	if(valid == true){

		cout << "\"" << input << "\" " << "is a palindrome permutation" << endl;
	}
	else{

		cout << "\"" << input << "\" " << "is not a palindrome permutation" << endl;
	}

  return (0);
}
bool is_palindrome(string input){

	unordered_map<char, int> palin; // map used to hold each character of the input and check each occurence of every letter
	int count = 0; // 

	for(unsigned int i = 0; i < input.size(); i++){

	  if(palin.find(input[i]) == palin.end()){ // if the letter does not exist already, set it's value to 1

		  palin[input[i]] = 1;
	  }
	  else{ // if the letter already exists, increment the value

		  palin[input[i]]++;
	  }
	}

	for(auto it = palin.begin(); it != palin.end(); it++){

		if((it->second % 2) == 1){ // checks to make sure there is at most only one letter that only occurs once(i.e. the middle of the palindrome)

			count++; // increment count to make sure this does not happen more than once.
			if(count > 1){ // if there are two letters this is true for, return false

				return false;
			}
		}
	}
	return true;

}
