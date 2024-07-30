// array of vectors
#include <bits/stdc++.h>
using namespace std;

int print_vector(vector<int> &v)
{
    cout << v.size() << endl;
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}
int main()
{
    int N;
    cin >> N;
    vector<int> vect[N]; // is array me har element ak vector hai
    for (int i = 0; i < N; i++)
    {
        int n, x;
        cin >> n;                   // vector ka size input le rahe hai nahi to wo to dyanamic nature ka hai to wo to kabhi katam hi ni hoga.
        for (int j = 0; j < n; j++) // har ak vector ka input le rahe hai
        {
            cin >> x;
            vect[i].push_back(x); // baki yea to simple jasea simple vector ko input lete hai wo hi hai
        }
    }
    for (int i = 0; i < N; i++)
        print_vector(vect[i]);
}