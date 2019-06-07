#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> find_match_case(int match,vector<int> arr){
	int nelement = arr.size();	//number of subset element
	vector< vector<int> > total_subset;
	
	for(int i=0; i < (1 << (nelement)); i++){
		vector<int> subset;
		for(int j=0;j<nelement;j++){
			if (i & (1<<j)){
				subset.push_back(arr[j]);
			}
		}
		int check=0;
		for(int k=0;k<subset.size();k++){
			check+=subset[k];
		}
		if(check==match)
			total_subset.push_back(subset);
	}
	return total_subset;
}
int main(int argc,char** argv){
	int N=5,S=0;
	vector<int> arr{-7,-3,-2,5,8};
	vector<vector<int>> result;
	result = find_match_case(S,arr);
	for(int i=0;i<result.size();i++){
		cout<<"num of "<< i<<" element case with sum "<<S<<endl;
		for (int j=0;j<result[i].size();j++){
			cout<<result[i][j]<<" ";
		}
		
		cout<<endl;
	}
}


