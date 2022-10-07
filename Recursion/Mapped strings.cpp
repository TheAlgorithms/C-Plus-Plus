/*We are given a hashmap which maps all the letters with number. Given 1 is mapped with A, 2 is mapped with B…..26 is mapped with Z. Given a number, you have
to print all the possible strings.

Input Format
A single line contains a number.

Constraints
Number is less than 10^6

Output Format
Print all the possible strings in sorted order in different lines.

Sample Input
123
Sample Output
ABC
AW
LC
Explanation
'1' '2' '3' = ABC
'1' '23' = AW
'12' '3' = LC*/

#include<iostream>
using namespace std;
void generate_strings(char *in,char *out,int i,int j){
	//base case
	if(in[i]=='\0'){
		out[j]='\0';
		cout<<out<<endl;
		return;
	}
	//recursive case
	//one digit at a time
	int digit=in[i]-'0';
	char ch=digit+'A'-1;
	out[j]=ch;
	generate_strings(in,out,i+1,j+1);
	
	//two digit at a time
	if(in[i+1]!='\0'){
		int seconddigit=in[i+1]-'0';
		int no=digit*10+seconddigit;
		if(no<=26){
			ch=no+'A'-1;
			out[j]=ch;
			generate_strings(in,out,i+2,j+1);
			
		}
	}
	return;
}
int main(){
	char in[1000000];
	cin>>in;
	char out[100];
	generate_strings(in,out,0,0);
	return 0;
}
