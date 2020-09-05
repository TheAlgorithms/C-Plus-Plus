#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

int main()
{
    int n;
    cout<<"Enter the dimension of the matrices: ";
    cin>>n;
    double a[n][n];
    cout<<"\nEnter the 1st matrix: \n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<"a["<<i<<"]["<<j<<"]= ";
            cin>>a[i][j];
        }
    }
     double b[n][n];
    cout<<"\nEnter the 2nd matrix: \n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<"b["<<i<<"]["<<j<<"]= ";
            cin>>b[i][j];
        }
    }
    cout<<"\nThe first matrix is:\n ";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            cout<<a[i][j]<<"\t";
            cout<<"\n";
    }
    cout<<"\n";
    cout<<"\nThe Second matrix is:\n ";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            cout<<b[i][j]<<"\t";
            cout<<"\n";
    }
    cout<<"\n";

    double c[n][n];
    cout<<"Enter the result matrix: \n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<"c["<<i<<"]["<<j<<"]= ";
            cin>>c[i][j];
        }
    }
    cout<<"The resultant matrix: \n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<c[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"\nrandom generation of the 'r' vector containing only 0/1 as it's elements\n";
    double r[n][1];
    for(int i=0;i<n;i++)
    {
        r[i][0]=rand() % 2;
        cout<< r[i][0]<< "\n";
    }
    cout<<"\nTest: a * (b*r) - (c*r) = 0\n";
    double br[n][1];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<1;j++)
        {
            for(int k=0;k<n;k++)
            br[i][j]=br[i][j]+ b[i][k]*r[k][j];

        }
    }
    double cr[n][1];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<1;j++)
        {
            for(int k=0;k<n;k++)
                cr[i][j]=cr[i][j]+c[i][k]* r[k][j];
        }
    }
    double abr[n][1];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<1;j++)
        {
            for(int k=0;k<n;k++)
                abr[i][j]=abr[i][j]+a[i][k]*br[k][j];
        }
    }
    /*cout<<"\nMatrix b*r \n";
     for(int i=0;i<n;i++)
    {
        for(int j=0;j<1;j++)
        {
            for(int k=0;k<n;k++)
            cout<<br[i][j]<<"\n";
        }
    }
    cout<<"\nMatrix c*r \n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<1;j++)
        {
            for(int k=0;k<n;k++)
                cout<<cr[i][j]<<"\n";
        }
    }
    cout<<"\nMatrix a*(b*r) \n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<1;j++)
        {
            for(int k=0;k<n;k++)
                cout<<abr[i][j]<<"\n";
        }
    }*/
    //abr-cr
    for(int i=0;i<n;i++)
    {
        abr[i][0]=abr[i][0]-cr[i][0];
    }
    cout<<"\nResult of a*(b*r)-(c*r): \n";
     for(int i=0;i<n;i++)
    {
        cout<<abr[i][0]<<"\n";
    }

    bool flag = true;
    for(int i=0;i<n;i++)
    {
        if(abr[i][0]==0)
            continue;
        else
            flag = false;
    }
    if (flag == true)
        cout<< "\nYes,'c' is the product of matrix a and b  ";
    else
        cout<< "\nNo";
}
