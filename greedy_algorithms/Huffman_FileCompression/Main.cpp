#include "Huff.cpp"

#pragma warning(disable : 4996)		//Disabling a waring concerning strcat function 

void String_to_char(string* ar, char** arr, int size);	 //Prototypes
void writeOnFile(char* cr, char** arr, int size);
void CompressionRate();

int main()	 //Driver Function
{
    Pque p;	 //User Defined Priority Queue
    Huffman H;	 //Huffman Object to print Codes
    string* ar; //String array to save the codes
    char** arr; //String array using Char to write the codes into the final file
    char* cr;	 //Character Array to Store characters

    p.ReadFile("TestFile.txt");	 //Reading the text file and loading the User Defined Priority Queue

    p.Traverse();	    //Printing The Queue
    cout << endl << endl;

    cr = new char[p.GetSize()];	 //Initialing the Character Array for Elements storage
    ar = new string[p.GetSize()];	 //Initialing the String Array for Huffman Codes storage

    H.Huffman_tree(p, ar, cr);	 //Implementing the Huffman tree as well as printing the codes

    arr = new char* [p.GetSize()];	 //Initalizing the String array using char
    for (int row = 0; row < p.GetSize(); ++row)
	   arr[row] = new char(ar[row].length() + 1);	//Initiailing each string according to its respective Code

    cout << endl << endl;
    String_to_char(ar, arr, p.GetSize());   //Coping the String Array into character string array

    for (int i = 0; i < p.GetSize(); i++)
	   cout << cr[i] << " : \t" << arr[i] << endl; //Printing the Codes

    writeOnFile(cr, arr, p.GetSize());	//Encoding the New text File using Huffman Codes
    CompressionRate();	   //Calculating and Printing Compressiong Rate 

    cout << endl << endl;

    system("pause");    //Pausing the Screen
    return 0;		//Successfull Termination of the Main/Driver Function
}

//Funtion that copies the string array into character string array for writing
void String_to_char(string* ar, char** arr, int size)
{
    for (int i = 0; i < size; i++)
    {
	   strcpy(arr[i], ar[i].c_str());	//This function does not work on Visual studio for some reason 
								//Hence the warning disable in the top of this page
    }
}

//Funtion that writes the codes in the new File
void writeOnFile(char* cr, char** arr, int size)
{
    string temp;	    //Temporary Variable to read the old text
    ifstream OldFile("TestFile.txt", ios::in);  //Opening the OldFile in Read Mode
    ofstream NewFile("CompressedFile.txt", ios::out);	 //Opening the NewFile in Witing Mode

    while (!OldFile.eof())	  //Reading the Old File
    {
	   OldFile >> temp;	   //Saving Words in temporary variable
	   temp += " ";    //Adding Spaces 
	   for (int i = 0; i < temp.length(); i++) //Replacing the characters with their Huffman Codes
	   {
		  int j = 0;  //Counter
		  while (j < size)
		  {
			 if (temp[i] == cr[j])	//Replacing Text to Code
			 {
				NewFile << arr[j];	//Writing on the file
				break;
			 }
			 j++;
		  }
	   }
    }
    OldFile.close();    //Closing the Files
    NewFile.close();
}

//Function to Calculate and Print the Compressiong Rate
void CompressionRate()
{
    int OldSize;	    //Temporary Variables
    int NewSize;
    string t = "";
    string c = "";
    ifstream OldFile("TestFile.txt", ios::in);  //Opening Files in Reading Modes
    ifstream NewFile("CompressedFile.txt", ios::in);
    while (!OldFile.eof())  //Reading Old File
    {
	   OldFile >> t;
	   c += t + " ";
    }
    OldSize = c.size() * 8;	  //Each Character/Symbol is stored as a 8 bit code
						  //So we Multiply the total number of characters with 8 to find the total size
						  //of the text
    c = "";	 //Reseting the Temporary Variable

    while (!NewFile.eof())  //Reading New File
    {
	   NewFile >> t;
	   c += t;
    }
    NewSize = c.size();		  //This text is simply the code given to a character 
						  //so each integer represents a bit

    cout << "File Size Before Compression = " << OldSize << " Bits " << endl;	//Print Statements
    cout << "File Size After Compression = " << NewSize << " Bits" << endl;
    cout << "Compression Rate = " << double(OldSize) / double(NewSize) << endl;	//Calculating Compression Rate
}