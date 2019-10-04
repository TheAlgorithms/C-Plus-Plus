#include <vector>
#include <iostream>
#include <utility> // pair
#include <algorithm> // sort

using namespace std;

int segments_union(const vector< pair <int,int> >& a) {
	
	int length = (int) a.size();

	vector < pair<int, bool> > x(length + length);
	
	for (int i = 0; i < length; i++) {
		x[i + i] = { a[i].first, true };
		x[i + i + 1] = { a[i].second, false }; 
	}
	
	sort(x.begin(), x.end());
	
	int answer = 0;
	int count = 0;
	
	for (int i = 0; i < length + length; i++) {
		
		if (count > 0 && i > 0) {
			answer += x[i].first - x[i - 1].first;
		}
		if (x[i].second == true) {
			++count;
		}
		else {
			--count;
		}
	}
	
	return answer;

}






int main() {
	
	vector<pair<int,int>> segments; // first - start, second - end of segment
	
	//   _____   _____
	// . . . . . . . . . .
	// 0 1 2 3 4 5 6 7 8 9
	// answer must be 2 + 2 = 4 
	
	segments.push_back( { 1, 3 } );
	segments.push_back( { 5, 6 } );
	segments.push_back( { 5, 7 } );
	
	cout << segments_union(segments) << endl;
	
	return 0;
}
