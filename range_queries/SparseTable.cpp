// Implementation of Sparse Table
//
// Running Time Complexity
// Build : O(NlogN)
// Range Query : O(1)


#include<iostream>
using namespace std;

#define INF     0x3f3f3f3f
#define int     long long
#define pii     pair<int, int>

const int N = 100005;
const int LOGN = 20;

int n;                  // length of the array
int A[N];
int logs[N];            // logs[i] = maximum p s.t. 2^p <= i
int table[LOGN][N];     // table[i][j] = [j, j+2^i]

void computeLogs(int n) {
    logs[1] = 0;
    for(int i = 2 ; i < n ; i++)
        logs[i] = logs[i/2] + 1;
}

void buildTable(int n) {
    int i, j, curLen;
    for(i = 0 ; i <= logs[n] ; i++) {
        curLen = 1LL<<i;
        for(j = 0 ; j + curLen < n ; j++) {
            if(curLen == 1)
                table[i][j] = A[j];
            else
                table[i][j] = min(table[i-1][j], table[i-1][j + curLen/2]);
        }
    }
}

int getMinimum(int beg, int end) {
    int p = logs[end - beg + 1];
    int pLen = 1LL << p;
    return min(table[p][beg], table[p][end - pLen + 1]);
}


int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int i, n, x;
    cout << "Enter the array length:";
    cin >> n;
    for(i = 0 ; i < n ; i++)
        cin >> A[i];
    computeLogs(n);
    buildTable(n);
    cout << "Minimum of the range [3, 14]: " << getMinimum(2,  13) << endl;
    return 0;
}