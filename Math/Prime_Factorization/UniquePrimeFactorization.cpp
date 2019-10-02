/*
Algo template for prime factorization (unique): O(sqrt(N))
Author: WilliamHYZhang
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<int> uniquePrimeFactors(int N){
	vector<int> pfs;
	int tmp = N;
	if(tmp%2 == 0){
		pfs.push_back(2);
		while(tmp%2 == 0)
			tmp /= 2;
	}
	for(int i = 3; i <= sqrt(tmp); i += 2){
		if(tmp%i == 0){
			pfs.push_back(i);
			while(tmp%i == 0)
				tmp /= i;
		}
	}
	if(tmp > 2)
		pfs.push_back(tmp);
	return pfs;
}

int main(){
	//Some examples
	cout << "Unique prime factors of 12345 are: ";
	for(auto &pf : uniquePrimeFactors(12345))
		cout << pf << " ";
	cout << endl;
}