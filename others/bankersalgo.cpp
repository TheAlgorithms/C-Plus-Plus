/*
 * @bankers_algorithm
 * @code for Bankers Algorithm both safety algorithm and resource request
 * @details
 * This contains the code for bankers algorithm. Input will be taken from user
 * @author Ananya (https://github.com/Ananya322)
 */

#include <iostream>

using namespace std;

int need[20][20], alloc[20][20], maximum[20][20], avail[20];
bool isFinished[20];
int safe[20];

void isSafe(int n, int m)
{
    int i, j, work[20], count = 0;
    for (i = 0; i < m; i++)
        work[i] = avail[i];
    for (i = 0; i < 20; i++)
        isFinished[i] = false;
    while (count < n)
    {
        bool canAllot = false;
        for (i = 0; i < n; i++)
        {
            if (isFinished[i] == false)
            {

                for (j = 0; j < m; j++)
                {
                    if (work[j] < need[i][j])
                    {
                        break;
                    }
                }
                if (j == m)
                {
                    for (j = 0; j < m; j++)
                    {
                        work[j] += alloc[i][j];
                    }

                    safe[count++] = i;
                    isFinished[i] = true;
                    canAllot = true;
                }
            }
        }
        if (canAllot == false)
        {
            cout << "Deadlock Condition\n";
            return;
        }
    }

    cout << "System is in safe state\n";

    cout << "Safe sequence: ";
    for (i = 0; i < n; i++)
        cout << "p" << safe[i] << "\t";
    cout << "\n";
}
int main()
{
    int i = 0, j = 0, k = 0, n, m, check, change;
    bool x;
    cout << "Enter number of Processes 'n': \n";
    cin >> n;
    cout << "Enter number of Resources'm': \n";
    cin >> m;

    int alloc[n][m], maximum[n][m], avail[m], req[m], need[n][m], res[m], temp[n], seq[n + 1];

    for (i = 0; i < m; i++)
    {
        res[i] = 0;
    }
    for (i = 0; i < m; i++)
    {
        avail[i] = 0;
    }

    cout << "\n Enter Allocation matrix: \n";
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            cin >> alloc[i][j];
        }
        cout << "\n";
    }

    cout << "\n Enter maximum matrix: \n";
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            cin >> maximum[i][j];
        }
        cout << "\n";
    }

    cout << "\n Enter available matrix: \n";
    for (j = 0; j < m; j++)
    {
        cin >> avail[j];
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            res[j] = res[j] + alloc[i][j];
        }
    }

    for (j = 0; j < m; j++)
    {
        res[j] = res[j] + avail[j];
    }

    cout << " \n The resource is : \n";
    for (j = 0; j < m; j++)
    {
        cout << "\t" << res[j];
    }
    cout << "\n";

    int a, counter = 0;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            a = maximum[i][j] - alloc[i][j];
            need[i][j] = a;
        }
    }

    cout << "\n need matrix is : \n";
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            cout << "\t" << need[i][j];
        }
        cout << "\n";
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (avail[j] >= need[i][j])
            {
                counter += 1;
            }
        }

        if (counter == m)
        {
            for (j = 0; j < m; j++)
            {
                avail[j] = alloc[i][j] + avail[j];
            }
            k++;
            seq[k] = i;
        }
        else
        {
            temp[i] = 1;
        }
        counter = 0;
    }

        isSafe(n, m);

    int indx, arr[20];
    cout << "Enter the process number for resource request: ";
    cin >> indx;

    cout << "Enter the requested instances of Each: ";
    for (j = 0; j < m; j++)
        cin >> arr[j];

    for (j = 0; j < m; j++)
    {
        if (need[indx][j] < arr[j] || arr[j] > avail[j])
        {
            cout << "Cannot request\n";
            break;
        }
    }

    if (j == m)
    {
        for (j = 0; j < m; j++)
        {
            alloc[indx][j] += arr[j];
            avail[j] -= arr[j];
            need[indx][j] -= arr[j];
        }

        cout << "need matrix:\n";
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                cout << "\t" << need[i][j];
            }
            cout << "\n";
        }

        cout << "\n Allocation matrix:\n";

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                cout << "\t" << alloc[i][j];
            }
            cout << "\n";
        }
    }
}
