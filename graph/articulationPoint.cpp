/*
15
15
0 1
1 2
2 9
0 7
7 8
8 9
3 9
9 4
9 10
10 11
5 13
6 13
14 13
11 12
12 13
*/
/*
6
7
5 0
0 1
1 2
1 3
2 3
2 4
3 4
*/
/*
7
8
5 0
0 1
1 2
1 3
2 3
2 4
3 4
5 6
*/
#include<bits/stdc++.h>
using namespace std;
// error shows 2 is ap
class ArticulationPair
{
    public:

    int vert;
    int disc;
    int low;
    bool isAP;
    bool processed;
    int parent=-1;
};
//static int graph[n][n];
//static ArticulationPair result[n];

void DFT(int time,int currv,int **graph,ArticulationPair *result[],int n)
{
    result[currv]->processed=true;
    result[currv]->disc=time;
    result[currv]->low=time;

    int rootChildCounter=0;

    for(int i=0;i<n;i++)
    {
        if(graph[currv][i]!=1)
        {
            continue;
        }

        if(result[i]->processed==false)
        {
            rootChildCounter++;
            result[i]->parent=currv;
            DFT(time+1,i,graph,result,n);
            result[currv]->low=min(result[currv]->low,result[i]->low);

            if(result[currv]->parent!=-1)
            {
                if(result[currv]->disc<=result[i]->low)
                {
                    result[currv]->isAP=new bool;
                    result[currv]->isAP=true;
                }
            }
            else
            {
                if(rootChildCounter > 1)
                {
                    result[currv]->isAP=new bool;
                    result[currv]->isAP=true;
                }
            }

        }
        else if(result[currv]->parent!=i)
        {
            result[currv]->low=min(result[currv]->low,result[i]->disc);
        }

    }

}

int main()
{
    int n,m;
    cin>>n;
    cin>>m;

    int **graph=new int*[n];
    for(int i=0;i<n;i++){
        graph[i]=new int[n];
    }
    ArticulationPair *result[n];

    for(int i=0;i<m;i++)
    {
        int x,y;
        cin>>x;
        cin>>y;
        graph[x][y]=1;
        graph[y][x]=1;
    }

    for(int i=0;i<n;i++)
    {
        result[i]=new ArticulationPair;
        result[i]->vert=i;
    }

    for(int i=0;i<n;i++)
    {
        if(result[i]->processed==true){
            continue;
        }
        DFT(0,i,graph,result,n);
    }

    vector<int> ap;
   for(int i=0;i<n;i++)
    {
        cout<<result[i]->vert<<" --> "<<result[i]->isAP<<endl;
        if(result[i]->isAP==true)
        {
            ap.push_back(result[i]->vert);
        }
    }

    for(int i=0;i<ap.size();i++){
        cout<<ap.at(i)<<"   ";
    }
   // cout<<result[0]->isAP;



    return 0;
}
