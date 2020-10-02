#include<iostream>
using namespace std;

/* 
        Warshalls Algorithm TO find All pair shortest path
        Coded By Vaibhav Gawai
*/
class graph
{
    int g[10][10]; // Matrix for Graph
    int n;
    public:
    graph()  // Constructor 
    {
        cout<<"Enter the number of nodes : ";
        cin>>n;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                g[i][j] = 999;
            }
        }
    }
    void getGraph()  //To Aceept the input from user
    {
        cout<<"ENter MAtrix in following way: \n\t-->Enter 0 for no self Loop\n\t-->Enter 999 for no direct edge\n\t-->OR Enter The weight\n";
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cout<<"Weight of "<<i+1<<" "<<j+1<<" : ";
                cin>>g[i][j];
            }
        }
    }
    void print()
    {
        cout<<"Your Graph Looks Like \n";
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cout<<g[i][j]<<"\t";
            }
            cout<<"\n";
        }
    }
    void warshalls()
    {
        int a[10][10];
        for(int k=0;k<n;k++)
        {
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n;j++)
                {
                    g[i][j] = min(g[i][j],g[i][k]+g[k][j]);
                }
            }
        }
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i!=j)
                    cout<<"Shortest Distance Between "<<i+1<<"to "<<j+1<<" is : "<<g[i][j]<<"\n";
            }
        }
        print();
    }   
};


int main()
{
    graph g1;
    g1.getGraph();
    g1.warshalls();
    return 0;
}