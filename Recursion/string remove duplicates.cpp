/*Take as input S, a string. Write a function that removes all consecutive duplicates. Print the value returned.

Input Format
String

Constraints
A string of length between 1 to 1000

Output Format
String

Sample Input
aabccba
Sample Output
abcba
Explanation
For the given example, "aabccba", Consecutive Occurrence of a is 2, b is 1, and c is 2.

After removing all of the consecutive occurences, the Final ans will be : - "abcba".*/

#include<iostream>
#include<cstring>
using namespace std;
void remove_duplicates(char a[]){
	int l=strlen(a);
	if(l==0 or l==1){
		return;
	}
	int pre=0;
	for(int current=1;current<l;current++){
		if(a[pre]!=a[current]){
			pre++;
			a[pre]=a[current];
			
		}
	}
	a[pre+1]='\0';
}
int main(){
	char a[1000];
	cin.getline(a,1000);
	remove_duplicates(a);
	cout<<a<<endl;
	return 0;
}
