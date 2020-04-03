#include<iostream>
#include<algorithm>
#include<string>

void permute(std::string str, long long num){
	long long i = 1;
	while(i<num)
		std::next_permutation(str.begin(),str.end());
	std::cout<<str;
}

int main(){
	std::string s = "0123456789";
	permute(s, 1000000);
	return 0;
}
	
