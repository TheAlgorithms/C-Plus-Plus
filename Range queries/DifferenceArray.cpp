/*
Starting with a 1-indexed array of zeros and a list of operations, 
for each operation add a value to each of the array element between two given indices, 
inclusive. Once all operations have been performed, return the maximum value in your array.
*/

/*
This program takes as input:
n the length of the array of zeroes.
m the length of the array of queries.
then it takes as input m queries in which each query contains 3 parameters l,r,v
where l is the left index, r is the right index, v is the value which has to be added in the range l to r.
*/

#include <bits/stdc++.h>

using namespace std;

long arrayManipulation(int n, vector<vector<int>> queries) {
    vector<long> vec(n, 0);
    for(int i = 0; i < queries.size(); i++){
        vec[queries[i][0] - 1] += queries[i][2];
        if(queries[i][1] < n)
            vec[queries[i][1]] -= queries[i][2];
    }
    for(int i = 1; i < vec.size(); i++)
        vec[i] = vec[i] + vec[i - 1];
    return *max_element(vec.begin(), vec.end());
}

int main()
{
	//n = length of array of zeroes
	//m = length of arrya of queries
    int n,m;
    cin>>n>>m;

    // array containing the queries
    vector<vector<int>> queries(m);
    for (int i = 0; i < m; i++) {
        queries[i].resize(3);
        for (int j = 0; j < 3; j++) {
            cin >> queries[i][j];
        }
    }

    long result = arrayManipulation(n, queries);
    cout<<result<<endl;
    return 0;
}
