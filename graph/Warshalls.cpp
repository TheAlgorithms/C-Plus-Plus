#include<iostream>
#include<conio.h>
 
using namespace std;
const int num_nodes = 10;
 
int main()
{
    int num_nodes, k, n;
    char i, j, res, c;
    int adj[10][10], path[10][10];
 
    cout << "\n\tMaximum number of nodes in the graph :";
    cin >> n;
    num_nodes = n;
    cout << "\n\n\tNODES ARE LABELED AS A,B,C,......\n\n";
    cout << "\nEnter 'y'for 'YES' and 'n' for 'NO' !!\n";
 
    for (i = 65; i < 65 + num_nodes; i++)
        for (j = 65; j < 65 + num_nodes; j++)
        {
            cout << "\n\tIs there an EDGE from " << i << " to " << j << " ? ";
            cin >> res;
            if (res == 'y')
                adj[i - 65][j - 65] = 1;
            else
                adj[i - 65][j - 65] = 0;
        }
    cout << "\nAdjacency Matrix:\n";
 
    cout << "\n\t\t\t   ";
    for (i = 0; i < num_nodes; i++)
    {
        c = 65 + i;
        cout << c << " ";
    }
    cout << "\n\n";
    for (int i = 0; i < num_nodes; i++)
    {
        c = 65 + i;
        cout << "\t\t\t" << c << "  ";
        for (int j = 0; j < num_nodes; j++)
            cout << adj[i][j] << " ";
        cout << "\n";
    }
    for (int i = 0; i < num_nodes; i++)
        for (int j = 0; j < num_nodes; j++)
            path[i][j] = adj[i][j];
 
    for (int k = 0; k < num_nodes; k++)
        for (int i = 0; i < num_nodes; i++)
            if (path[i][k] == 1)
                for (int j = 0; j < num_nodes; j++)
                    path[i][j] = path[i][j] || path[k][j];
 
    for (int i = 0; i < num_nodes; i++)
        for (int j = 0; j < num_nodes; j++)
            adj[i][j] = path[i][j];
 
    cout << "\nTransitive Closure of the Graph:\n";
 
    cout << "\n\t\t\t   ";
    for (i = 0; i < num_nodes; i++)
    {
        c = 65 + i;
        cout << c << " ";
    }
    cout << "\n\n";
    for (int i = 0; i < num_nodes; i++)
    {
 
        c = 65 + i;
        cout << "\t\t\t" << c << "  ";
        for (int j = 0; j < num_nodes; j++)
            cout << adj[i][j] << " ";
        cout << "\n";
    }
    return 0;
}
