#include<bits/stdc++.h>
using namespace std;

/*==================================================
     DSU FIND FUNCTION (path compression)
===================================================*/
int find(vector<pair<int,int>>&trees, int i) 
{ 
    // find root and make root as parent of i 
    if (trees[i].second != i) 
        trees[i].second = find(trees, trees[i].second); 
    return trees[i].second; 
} 


/*====================================================
     DSU UNION FUNCTION (union by comparing rank)
=====================================================*/
void Union(vector<pair<int,int>>&trees, int a, int b) 
{ 
    int rootA = find(trees, a); 
    int rootB = find(trees, b); 

    // merge smaller tree to larger one by comparing rank
    if (trees[rootA].first < trees[rootB].first) 
        trees[rootA].second = rootB; 
    else if (trees[rootA].first > trees[rootB].first) 
        trees[rootB].second = rootA; 

    // If ranks are same
    else
    { 
        trees[rootB].second = rootA; 
        trees[rootA].first++; 
    } 
}

/*========================================================
            BORUVKA'S ALGORITHM MAIN FUNCTION
=========================================================*/
void Boruvkas_function(vector<vector<int>>Graph,int V,int E) 
{ 

    //Create a vector of pairs for V different trees.
    //Pair is used for storing rank and parent (DSU)  
    vector<pair<int,int>>trees;

    // Create V single-vertex trees  
    for (int i = 0; i < V; i++) 
    { 
        trees.push_back(make_pair(0,i));
    } 
    //Initialising two variables
    //TotalTrees stores total no. of trees
    //MST_total_weight stores total weight of MST
    int TotalTrees = V; 
    int MST_total_weight = 0; 


    cout<<"Edges of MST are :-"<<endl;
    //Loop till only one tree(MST) left
    while (TotalTrees > 1) 
    { 
        //A vector is created to store smallest edge 
        //of each tree. And initialised to -1
        vector<int> smallest_edge(V,-1);

        // Traverse through all edges and update 
        // smallest_edge of every tree 
        for (int i=0; i<E; i++) 
        { 
            // Find trees of vertices(s-d) of current edge
            int setA = find(trees, Graph[i][0]); 
            int setB = find(trees, Graph[i][1]); 

            // If two vertices of current edge belong to 
            //same tree -->continue
            if (setA == setB) 
                continue; 

            // Else check if current edge is closer to previous 
            // smallest_edge edges of setA and setB 
            else
            { 
            if (smallest_edge[setA] == -1 || 
                Graph[smallest_edge[setA]][2] > Graph[i][2]) 
                smallest_edge[setA] = i; 

            if (smallest_edge[setB] == -1 || 
                Graph[smallest_edge[setB]][2] > Graph[i][2]) 
                smallest_edge[setB] = i; 
            } 
        } 

        //Add edges to MST
        for (int i=0; i<V; i++) 
        { 
            //if smallest_edge for current set exists 
            if (smallest_edge[i] != -1) 
            { 
                int setA=find(trees, Graph[smallest_edge[i]][0]); 
                int setB=find(trees, Graph[smallest_edge[i]][1]); 

                //if they belong to same tree -->continue
                if (setA == setB) 
                    continue; 
                //calculate the total weight of MST
                MST_total_weight += Graph[smallest_edge[i]][2]; 

                //Displaying output edges of final MST
                cout<<"Edge ("<<Graph[smallest_edge[i]][0]<<","
                    <<Graph[smallest_edge[i]][1]<<") "<<"weight "
                    <<Graph[smallest_edge[i]][2]<<endl; 

                //If two trees are not same then do the union
                //and decrement the no. of trees
                Union(trees, setA, setB); 
                TotalTrees--; 
            } 
        } 
    } 
    //Displaying Total weight of  MST
    cout<<"Total weight of MST is:"<<MST_total_weight<<endl; 
} 

/*======================================
             MAIN FUNCTION
=======================================*/
int main() 
{ 
    /*  GIVEN GRAPH 
               3
        1-------------2 
        | \ 13        |
        |   \         |
        |     5       |
       4|       \     |9
        |         \ 2 |
        |           \ |
        4-------------3 
               8               */

    int V = 5; // Number of vertices
    int E = 6; // Number of edges

    //Creating 2D vector for graph
    vector<vector<int>>Graph;
    //Inserting edge (1,2) weight:3
    Graph.push_back({1,2,3});
    //Inserting edge (1,4) weight:4
    Graph.push_back({1,4,4});
    //Inserting edge (1,5) weight:13
    Graph.push_back({1,5,13});
    //Inserting edge (2,3) weight:9
    Graph.push_back({2,3,9});
    //Inserting edge (5,3) weight:2
    Graph.push_back({5,3,2}); 
    //Inserting edge (3,4) weight:8
    Graph.push_back({3,4,8}); 
    //Calling Boruvkas_function()
    Boruvkas_function(Graph,V,E); 

    return 0; 
}
