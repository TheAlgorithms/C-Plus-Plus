#include<iostream>
using namespace std;

void towerOfHanoi(int n, char from_rod, char to_rod,char aux_rod, string &ans)
{
	if (n == 0) {
		return;
	}
	towerOfHanoi(n - 1, from_rod, aux_rod, to_rod, ans);
    ans += "Moved disk " + to_string(n) + " from rod " + from_rod + " to rod " + to_rod + ", ";
	towerOfHanoi(n - 1, aux_rod, to_rod, from_rod, ans);
}

bool test() {
	int N = 3;
    string expectedOutput = "Moved disk 1 from rod A to rod C, Moved disk 2 from rod A to rod B, Moved disk 1 from rod C to rod B, Moved disk 3 from rod A to rod C, Moved disk 1 from rod B to rod A, Moved disk 2 from rod B to rod C, Moved disk 1 from rod A to rod C";
    string actualOutput;
    towerOfHanoi(N, 'A', 'C', 'B', actualOutput);
    while(isspace(actualOutput.back()) or actualOutput.back() == ',') actualOutput.pop_back();
    return (expectedOutput == actualOutput);
}

// Driver code
int main()
{
	if(test()) cout<<"Working Fine\n";
    else cout<<"Needs Correction\n";
	return 0;
}
