#include <iostream>
# define n 8

/**
A knight's tour is a sequence of moves of a knight on a chessboard
such that the knight visits every square only once. If the knight 
ends on a square that is one knight's move from the beginning 
square (so that it could tour the board again immediately, following 
the same path), the tour is closed; otherwise, it is open.
**/

using namespace std;
bool issafe(int x,int y,int sol[n][n])
{
    return (x<n && x>=0 && y<n && y>=0 && sol[x][y]==-1);

}
bool solve(int x,int y, int mov, int sol[n][n], int xmov[n], int ymov[n])
{
    int k,xnext,ynext;

    if(mov == n*n)
        return true;

    for(k=0;k<8;k++)
    {
        xnext=x+xmov[k];
        ynext=y+ymov[k];

        if(issafe(xnext,ynext,sol))
            {
                sol[xnext][ynext]=mov;

                if(solve(xnext,ynext,mov+1,sol,xmov,ymov)==true)
                    return true;
                else
                    sol[xnext][ynext]=-1;
            }
    }
    return false;
}
int main()
{
    //initialize();

    int sol[n][n];
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            sol[i][j]=-1;

    int xmov[8] = {  2, 1, -1, -2, -2, -1,  1,  2 };
    int ymov[8] = {  1, 2,  2,  1, -1, -2, -2, -1 };
    sol[0][0]=0;

    bool flag=solve(0,0,1,sol,xmov,ymov);
    if(flag==false)
        cout<<"solution doesnot exist \n";
    else
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
                cout<<sol[i][j]<<"  ";
            cout<<"\n";
        }
    }
}
