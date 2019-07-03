#include<iostream>

using namespace std; 

int minimax(int depth, int nodeIndex, bool isMax, int scores[], int height) {

	if (depth == height) 
		return scores[nodeIndex]; 

	if (isMax) 
		return max(minimax(depth + 1, nodeIndex * 2, false, scores, height), minimax(depth + 1, nodeIndex * 2 + 1, false, scores, height)); 
	return min(minimax(depth + 1, nodeIndex * 2, true, scores, height), minimax(depth + 1, nodeIndex * 2 + 1, true, scores, height)); 

} 

int log2(int number) { 
	if (number == 1)
		return 0;
	return (1 + log2(number / 2)); 
} 

int main() {
	int scores[] = {90, 23, 6, 33, 21, 65, 123, 34423};
	int size = sizeof(scores) / sizeof(scores[0]); 
	int height = log2(size);
	int result = minimax(0, 0, true, scores, height);
	cout << "Optimal move " << result << endl; 
	return 0;
}
