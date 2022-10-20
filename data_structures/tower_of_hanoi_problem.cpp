#include <iostream>
using namespace std;

void tower_of_hanoi(int n, char rod1, char rod2, char rod3) {
    if (n == 0)  // condition when no disk is present
        return;
    tower_of_hanoi(n - 1, rod1, rod3, rod2);  // recursive calling of function
    cout << "Place disk " << n << "from rod " << rod1 << "to rod " << rod2
         << endl;
    tower_of_hanoi(n - 1, rod3, rod2, rod1);
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        int N;  // N represent number of disks
        cin >> N;
        tower_of_hanoi(N, 'A', 'C', 'B');  // A,B,C are rods
    }
    return 0;
}
