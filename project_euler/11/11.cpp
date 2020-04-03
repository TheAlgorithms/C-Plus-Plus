#include <iostream>
#include <fstream>

using namespace std;

int main(){
	int grid[20][20];
	long long high = 0, temp = 0;
	fstream file("problem-11.txt");
	int n, i = 0, j = 0;
	while (file >> n){
		grid[i][j++] = n;
		if (j == 20){
			i++;
			j = 0;
		}
	}
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (i < 17){
				temp = grid[i][j] * grid[i + 1][j] * grid[i + 2][j] * grid[i + 3][j];
				high = (temp > high) ? temp : high;
			}
			if (j < 17){
				temp = grid[i][j] * grid[i][j + 1] * grid[i][j + 2] * grid[i][j + 3];
				high = (temp > high) ? temp : high;
			}
			if (i < 17 && j < 17){
				temp = grid[i][j] * grid[i + 1][j + 1] * grid[i + 2][j + 2] * grid[i + 3][j + 3];
				high = (temp > high) ? temp : high;
			}
			if (i <17 && j > 2){
				temp = grid[i][j] * grid[i + 1][j - 1] * grid[i + 2][j - 2] * grid[i + 3][j - 3];
				high = (temp > high) ? temp : high;
			}
		}
	}
	cout << high << endl;
    file.close();
	return 0;
}
