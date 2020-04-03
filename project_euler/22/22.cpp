#include<fstream>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<sstream>



long long alpha(char a){
	return (int)a - '@';
}

long long count(std::string str){
	long long ans=0;
	for(int i=0;i<str.size();++i){
		ans += alpha(str[i]);
	}
	return ans;
}


int main(){
	std::vector<std::string> names;
	std::fstream file("names.txt", std::fstream::in);
	std::string str;
	long long ans=0;
	while(getline(file,str,'"')){
		if(str[0]!= ',')
			names.push_back(str);
	}
	std::sort (names.begin(), names.end());
	for(int i = 0; i<names.size();++i)
		ans += i * count(names[i]);
	std::cout<<ans<<std::endl;
	return 0;
}
