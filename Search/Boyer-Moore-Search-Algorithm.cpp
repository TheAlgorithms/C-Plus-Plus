#include<iostream>
#include<memory.h>

using namespace std;

//fastest string searching algorithm

int main()
{
    int Tindex, Pindex, TindexStart;
    int BMt[256];                                             //skipping count hashtable for each character
    string text, pattern;
    cout<<"Enter the text: \n";
    getline(cin, text);                                       //the paragraph in which a word going to be searched
    cout<<"Enter the pattern to be searched: \n";
    cin>>pattern;                                             //the searching word (pattern word)

    for(int index=0; index<256; index++)
        BMt[index] = pattern.length();                        //storing pattern word length for all the characters initially
    
    for(int index=0; index<pattern.length()-1; index++)
        BMt[pattern[index]] = pattern.length()-index-1;       //altering the skipping values only for the pattern word characters, that denotes for that character how characters have to be skipped
    
    Pindex = pattern.size()-1;
    for(Tindex=pattern.size()-1; Tindex<text.size(); )        //this algorithm matching goes from last character of the pattern to the first, instead of naive forward checking
    {
        TindexStart = Tindex;
        while(Pindex>=0 && text[Tindex]==pattern[Pindex])     //if matching character, then checks for successive other characters
        {
            Tindex--;
            Pindex--;
        }
        if(Pindex<0)                                          //if pattern iterator goes beyond value 0, then it means it checked for all characters and all characters are matched
            cout<<"Pattern Found at :"<<Tindex+1<<endl;

        Tindex = BMt[text[TindexStart]] + TindexStart;        //else pattern is not found, then skipping the pattern to value times corresponding to mismatch character in BMt table
        Pindex = pattern.size()-1;                            //restarting the pattern index to the end
    }
    return 0;
}
//contributed by Sathvik S
