/**
 *
 * \file
 * \brief [Breadth First Search Algorithm
 * (Breadth First Search)](https://en.wikipedia.org/wiki/Breadth-first_search)
 *
 * \author [Ayaan Khan](http://github.com/ayaankhan98)
 *
 *
 * \details
 * Breadth First Search also quoted as BFS is a Graph Traversal Algorithm.
 * Time Complexity O(|V| + |E|) where V are the number of vertices and E
 * are the number of edges in the graph.
 *
 * Applications of Breadth First Search are
 *
 * 1. Finding shortest path between two vertices say u and v, with path
 *    length measured by number of edges (an advantage over depth first
 *    search algorithm)
 * 2. Ford-Fulkerson Method for computing the maximum flow in a flow network.
 * 3. Testing bipartiteness of a graph.
 * 4. Cheney's Algorithm, Copying garbage collection.
 *
 * And there are many more...
 *
 * <h4>working</h4>
 * In the implementation below we first created a graph using the adjacency
 * list representation of graph.
 * Breadth First Search Works as follows
 * it requires a vertex as a start vertex, Start vertex is that vertex
 * from where you want to start traversing the graph.
 * We maintain a bool array or a vector to keep track of the vertices
 * which we have visited so that we do not traverse the visited vertices
 * again and again and eventually fall into an infinite loop. Along with this
 * boolen array we use a Queue.
 *
 * 1. First we mark the start vertex as visited.
 * 2. Push this visited vertex in the Queue.
 * 3. while the queue is not empty we repeat the following steps
 *
 *      1. Take out an element from the front of queue
 *      2. Explore the adjacency list of this vertex
 *         if element in the adjacency list is not visited then we
 *         push that element into the queue and mark this as visited
 *
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <list>
#include <string>


/* Class Graph definition */
template<typename T>
class Graph{
  /**
  *  adjacency_list maps every vertex to the list of its neighbours in the order
  *  in which they are added.
  */
  std::map<T,std::list<T> > adjacency_list;
  public:
    Graph(){};
    void add_edge(T u,T v, bool bidir=true){
      /**
      *  add_edge(u,v,bidir) is used to add an edge between node u and node v
      *  by default , bidir is made true , i.e graph is bidirectional .
      *  It means if edge(u,v) is added then u-->v  and  v-->u both edges exist.
      *
      *  to make the graph unidirectional pass the third parameter of add_edge as
      *  false which will
      */
      adjacency_list[u].push_back(v);               // u-->v edge added
      if(bidir==true){
        // if graph is bidirectional
        adjacency_list[v].push_back(u);             // v-->u edge added
      }
    }
    /**
    *  this function performs the breadth first search on graph and return a
    *  mapping which maps the nodes to a boolean value representing whether the
    *  node was traversed or not.
    */
    std::map<T,bool> breadth_first_search(T src){
      std::map<T,bool> tracker;

      for(auto adjlist: adjacency_list){
        tracker[adjlist.first]=false;
        for(auto node:adjacency_list[adjlist.first]){
          tracker[node]=false;
        }
      }
      std::queue<T> q;
      q.push(src);
      tracker[src]=true;
      while(!q.empty()){
        T node = q.front();
        q.pop();
        for(T neighbour : adjacency_list[node]){
          if(!tracker[neighbour]){
            q.push(neighbour);
            tracker[neighbour]=true;
          }
        }
      }
      return tracker;
    }
};

/** Test function */
static void tests() {
    /// Test 1 Begin
    Graph<int> g;
    std::map<int,bool> correct_result;
    g.add_edge(0,1);
    g.add_edge(1,2);
    g.add_edge(2,3);
    correct_result[0]=true;
    correct_result[1]=true;
    correct_result[2]=true;
    correct_result[3]=true;

    std::map<int,bool> returned_result = g.breadth_first_search(2);

    assert(returned_result==correct_result);
    std::cout << "Test 1 Passed..." << std::endl;

    /// Test 2 Begin
    returned_result = g.breadth_first_search(0);

    assert(returned_result==correct_result);
    std::cout << "Test 2 Passed..." << std::endl;

    /// Test 3 Begins
    // 0-> Gorakhpur
    // 1-> Lucknow
    // 2-> Kanpur
    // 3-> Agra
    // 4-> Prayagraj
    // 5-> Noida
    Graph<std::string> g2;

    g2.add_edge("Gorakhpur","Lucknow",false);
    g2.add_edge("Gorakhpur","Kanpur",false);
    g2.add_edge("Lucknow","Agra",false);
    g2.add_edge("Kanpur","Agra",false);
    g2.add_edge("Lucknow","Prayagraj",false);
    g2.add_edge("Agra","Noida",false);

    std::map<std::string,bool> correct_res;
    std::map<std::string,bool> returned_res=g2.breadth_first_search("Kanpur");
    correct_res["Gorakhpur"]=false;
    correct_res["Lucknow"]=false;
    correct_res["Kanpur"]=true;
    correct_res["Agra"]=true;
    correct_res["Prayagraj"]=false;
    correct_res["Noida"]=true;
    for(auto x: returned_res){
      std::cout<<x.first<<" : "<<x.second<<std::endl;
    }
    assert(correct_res==returned_res);
    std::cout << "Test 3 Passed..." << std::endl;

}

/** Main function */
int main() {
    tests();
/*
    size_t vertices = 0, edges = 0;
    std::cout << "Enter the number of vertices: ";
    std::cin >> vertices;
    std::cout << "Enter the number of edges: ";
    std::cin >> edges;

    graph::adjacency_list graph(vertices);

    std::cout << "Enter space-separated pairs of vertices that form edges: "
              << std::endl;
    while (edges--) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        // Decrement the vertex index so that we can read more convenint
        // 1-based indexing from the user input.
        graph::add_directed_edge(&graph, u - 1, v - 1);
    }

    graph::breadth_first_search(graph, 0);
*/
    return 0;
}
