/**

 * @file
 * @brief Demonstrates how to create a graph using Adjacency list representation.
 * @details Takes user input to create either a directed or undirected graph.
 *          Include input validation and prints the final graph structure.

*/

#include <iostream>
#include <vector>

using namespace std;

//Graph class

class Graph{

private:
    int V;
    vector<vector<int>> adj;
    bool directed;

public:
    Graph(int V, bool directed ){
        this->V = V;
        this->directed = directed;
        adj.resize(V);
    }
    void addEdge(int from , int to){
        if(from>=V || to>=V || from<0 || to<0){                   //Checking if given vertices are inside the bound of (0-[V-1]).
            cout<<"Error: vertex out of bound!!!\n";
            return;
        }
        adj[from].push_back(to);
        if(directed == false )
            adj[to].push_back(from);
    }

    void printGraph() {
        cout<<"The Graph Representation by Adjacency List:\n";
        for(int i=0 ; i<V ; i++){
            cout<<"Node "<<i<<": ";
            for(int adjacentNode : adj[i])
                cout<<adjacentNode<< " ";
            cout<<endl;
        }
    }
};



int main()
{
    int V;
    do{

    cout<<"Enter number of Nodes in the Graph:";
    cin>>V;
    cin.ignore();
    if(V>INT_MAX || V<1)                                        // Checking to limit the input size between [0 - INT_MAX]
        cout<<"Enter a valid positive number!!\n";
    }while(V>INT_MAX || V<1);

    /*----Whether the Graph will be directed or not----*/
    int isDirected;

    do{
    cout<<"Is this graph directed (0=No , 1=Yes):";
    cin>>isDirected;
    }while(isDirected != 0 && isDirected !=1);

    Graph g(V,isDirected);  //Initializing the Graph object.

    /*----Creating edges of the graph----*/
    cout<<"Create edges (enter pairs of connected nodes):\n";
    int addMore;
    do{
        int from , to;
        cout<<"From Node:";
        cin>>from;
        cout<<"To Node  :";
        cin>>to;
        g.addEdge(from ,to);
        cout << "Do you want to add another edge? (1 = yes, 0 = no): ";
        cin>>addMore;                                                       // A flag value to let user decided when to stop.
    }while(addMore>0);

    cout<<"\nGraph creation complete.\n";
    g.printGraph();                 //To Print the created graph of V nodes.

    return 0;
}
