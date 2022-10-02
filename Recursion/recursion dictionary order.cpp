/*Take as input str, a string. Write a recursive function which prints all the words possible by rearranging the characters of this string which are in dictionary
 order larger than the given string.
The output strings must be lexicographically sorted.

Input Format
Single line input containing a string

Constraints
Length of string <= 10

Output Format
Display all the words which are in dictionary order larger than the string entered in a new line each. The output strings must be sorted.

Sample Input
cab

Sample Output
cba
Explanation
The possible permutations of string "cab" are "abc" , "acb" ,"bac" , "bca" , "cab" and "cba" . Only one of them is lexicographically greater than "cab". We only
 print "cba".*/
 
#include<iostream>
#include<set>
#include<string>
using namespace std;
string input;
void permute(string in,int i,set<string> &s){
	//base case
	if(in[i]=='\0'){
		//cout<<in<<" , ";
		string t(in);
        if(in>input){
		    s.insert(t);
        }
		return;
	}

	
	
	//recursive case
	for(int j=i;in[j]!='\0';j++){
		swap(in[i],in[j]);
		permute(in,i+1,s);
		//restore the original array (backtracking)
		swap(in[i],in[j]);
	}
	
	
	
}

int main(){

	cin>>input;
	set<string> s;
	
	permute(input,0,s);
	//loop over the s
	for(auto str:s){
		cout<<str<<"\n";
	}
}
