#include <bits/stdc++.h>
using namespace std;
 
#define all(c) c.begin(), c.end()
 
// Each job is represented as a pair of int and pair


typedef pair<int, pair<int, int> > job;
 
// compare function is given so that we can specify how to compare a pair of jobs 
bool cmp_pair(job a, job b)
{
    int a_Li, a_Ti, b_Li, b_Ti;
    a_Li = a.second.first;
    a_Ti = a.second.second;
    b_Li = b.second.first;
    b_Ti = b.second.second;
 
    // To compare a/b and c/d, compare ad and bc
    return (a_Li * b_Ti) > (b_Li * a_Ti);
}
 
void printOptimal(int L[], int T[], int n)
{
    vector<job> list; // (Job Index, Si, Ti)
 
    for (int i = 0; i < n ; i++) {
        int t = T[i];
        int l = L[i];
 
        // Each element is: (Job Index, (Li, Ti) )
        list.push_back(make_pair(i + 1, make_pair(l, t)));
    }
 
    stable_sort(all(list), cmp_pair);
 
    // traverse the list and print job numbers
    cout << "Job numbers in optimal sequence are\n";
    for (int i = 0; i < n; i++)
        cout << list[i].first << " ";
 
}
 
// main function
int main()
{
    int n;
    cin>>n;
    int job1[n], job2[n];
    for (int i=0; i<n; i++){
    	cin>>job1[i];
	}
	
	for (int i=0; i<n; i++){
    	cin>>job2[i];
	}
	
    printOptimal(job1, job2, n);
    return 0;
}