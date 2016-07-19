 #include <iostream>
#include <string> 

using namespace std;
char paragraph;


int main()
{
	string paragraph;
	cout << "Please enter your paragraph:";
	getline (cin,paragraph);
	cout << "Hello, your paragraph is " << paragraph << "!\n";
	string paragraph1 = paragraph;
	//string sentence = paragraph + " " +paragraph + " " + paragraph;
	//cout << sentence << endl;
	cout << "The size of your paragraph = " << paragraph.size() << " characters. \n\n";
	string word;
	cout << "Please enter the word you are searching for:";
		getline (cin,word);

		cout << "Hello, your word is " << word << "!\n";

	

bool wordsearch = true;
	do {
		if (paragraph.find(word) == string::npos)
		cout << "" << word << " does not exist in the sentence" << endl;

		cout << "The word " << word << " is now found at location " << paragraph.find(word) << endl << endl;


		
		if (paragraph.empty())
	{
		cout << "\nThe sentence is empty" << endl;
	}
	else
		cout << "\nThe sentence is not empty" << endl;

	system ("pause");
	
	}while (wordsearch = true);
}