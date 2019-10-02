#include <iostream>

using namespace std;
#define N 100  

// 8 directions
char DIR[8][2] = {
  {1,0}, {1,-1}, {1,1}, {0,-1}, {0,1}, {-1,0}, {-1,-1}, {-1,1}
};
// for total array size and counter
int m, n, count;

// method for finding word presence in the array in a specific direction
bool match(char CharMat[100][100], char word[], int i, int j, int dir_index)
{
    int k=0;
    for( ; i<m  && j<n  && i>=0  && j >=0  && word[k] != '\0'; i = i+DIR[dir_index][0],  j = j+DIR[dir_index][1], k++)
    if(word[k] != CharMat[i][j])
        return false;
    // end of char
    if (word[k] == '\0')
        return true;
    return false;  
}

void find_presence(char CharMat[100][100], char word[])
{
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            if (CharMat[i][j] == word[0])
                for (int k=0; k<8; k++)
                    if (match(CharMat, word, i, j, k)) {
                        count++;
                    }
}

int main()
{
    char CharMat[N][N];
    int T;
    cin >> T;
    for(int t=0;t<T;t++){
        count = 0;
        cin >> m;
        cin >> n;
        for (int i=0; i<m; i++)
            cin >> CharMat[i];
        
        char word[N];
        cin >> word;
        find_presence(CharMat, word);
        cout << "Case " << t+1 << ": " << count << endl;
    }
}