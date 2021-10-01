/**
 * \file
 * \brief [Bellman Ford Algorithm]
 * (https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm)
 *
 * 
 * @details
 * Bellman Ford algorithm is an alogirthm used for finding shortest 
 * path on an edge weighted directed graph.
 *
 * It is similar to djikstra's algorithm, but the problem with djisktra's algrorithm is that 
 * it do not asssume negative weights.
 * Bellman Ford works well with negative weights.
 * When we are sure there is no negative cycle present, then we can use djisktra's algorithm, but 
 * when we are not sure, we can not use djikstra, because it does not work, but bellman ford work
 *
 *
 * IDEA:
 * - Let |V| be the number of vertices and |E| be the edges.
 * - Create an array dist with size |V|. Initialize distance from source to all vertices 
 *   as infinte and to the source, 0
 * - Do following |V|-1 times
 *     for each e-v edge in graph,
 *       if dist[v]> dist[u] + weight of edge u-v, then dist[v] = dist[u] + weight of edge u-v
 * - repeat the above step, i.e 
 *     for each e-v edge in graph,
 *       if dist[v]> dist[u] + weight of edge u-v ,
 *          then, this means there is a negative weight cycle, for such a graph no shortest path exists.
 * (https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/)
 *
 *
 * @author [Animesh Gupta](https://github.com/handle)
 */

#include<iostream>
#include<vector>
#include<queue>
#include<unordered_set>
#define INT32_MAX 2147483647
#define graph_size 13
using namespace std;
struct graph_element{
    int start;
    int end;
    int weight;
    graph_element(int a, int b, int c){
        start = a-1;
        end = b-1;
        weight = c;
    }
};
int main(){
    int s,e,w; // temporary variable to store immediate graph element
    int n,m,src; 
    // sample input
    int graph_input[][3] = {
                            {10, 12, 1},
                            {1, 2, 10},
                            {3, 2, 1},
                            {3, 4, 1},
                            {4, 5, 3},
                            {5, 6, -1},
                            {7, 6, -1},
                            {8, 7, 1},
                            {1, 8, 8},
                            {7, 2, -4},
                            {2, 6, 2},
                            {6, 3, -2},
                            {9, 10, -2},
                            };
    src = 1;
    int start_vertex = src-1;
    unordered_set<int> setr; // to store unique vertices
    vector<graph_element> graph; // vector of structure comprising starting edge, ending edge, and the weight
    for(int i=0;i<graph_size;i++){
        s = graph_input[i][0];
        e = graph_input[i][1];
        w = graph_input[i][2];
        setr.insert(s);
        setr.insert(e);
        // populating the graph data structure defined as vector of structure
        graph.push_back(graph_element(s,e,w));
    }



    int vertices = setr.size();
    // intialise the array
    vector<int> global_weight_array(vertices,INT32_MAX);

    // marking distance to source 0, 
    global_weight_array[start_vertex]=0;

    for(int j=0;j<vertices-1;j++){
        for (auto i: graph){
            if(i.end!=start_vertex ){
                if((global_weight_array[i.end] > global_weight_array[i.start]+i.weight) && (global_weight_array[i.start]!=INT32_MAX)){
                    global_weight_array[i.end] = global_weight_array[i.start]+i.weight;
                }
            }
        }
    }
    for (auto i: graph){
            if((global_weight_array[i.end] > global_weight_array[i.start]+i.weight) &&(global_weight_array[i.end]!=INT32_MAX && global_weight_array[i.start]!=INT32_MAX) ){
                cout<<"graph contains negative weight cycle\n";
                return 0;
            }
    }
    for(int i=0;i<vertices;i++){
        if(start_vertex==i) continue;
        if(global_weight_array[i]==INT32_MAX){
            cout<<src<<" "<< i+1 <<" "<< "infinite" <<"\n";
            continue;
        }
        cout<<src<<" "<< i+1 <<" "<< global_weight_array[i] <<"\n";
    }
    cout<<endl;

}



// expected output
// 1 2 5
// 1 3 5
// 1 4 6
// 1 5 9
// 1 6 7
// 1 7 9
// 1 8 8
// 1 9 infinite
// 1 10 infinite

