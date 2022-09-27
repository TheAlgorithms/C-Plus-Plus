/**
 *
 * \file
 * \brief [Graph Connected Components
 * (Connected Components)]
 * (https://en.wikipedia.org/wiki/Component_(graph_theory))
 *
 * \author [Ritik Rathor](https://github.com/ritik-369)
 *
 * \details
 * A graph is a collection of nodes also called vertices and these vertices
 * are connected by edges. A connected component in a graph refers to a set of
 * vertices which are reachable form one another.
 *
 * <pre>
 * Example - Here is graph with 3 connected components
 *
 *      1   4           5               8
 *     / \ /           / \             / \
 *    2---3           6   7           9   10
 *
 *    first          second           third
 *    component      component        component
 * </pre>
 *
 */


//                  WE WILL LEARN CALCULATING NO. OF CONNECTED COMPONENTS IN GRAPH USING BFS BY SOLVING A HACKEREARTH QUESTION
//                  LINK=   https://www.hackerearth.com/problem/algorithm/connected-components-in-a-graph/


#include <iostream>  // for IO operations
#include <vector>    //for using vectors to make graph or adjacency list
#include <queue>     //for using queue data structure for pushing and poping nodes during bfs

/**
 * @brief connected_components_bfs function
 * @returns number of connected components on exit
 */
int connected_components_bfs(std::vector<std::vector<int>>adj,int nodes) // {adj} is adjacency list of graph and {nodes} is number of nodes in graph 
{
   int components=0;          // initialize no. of components in graph as 0
   int start=1;              // source node declaration as number 1 we can assign 0 if number of nodes starts from zero
   int end=(nodes+start-1);
   std::vector<bool>vis(nodes+1,0);  // vector for visited node used during running of bfs
   std::queue<int>q;                  // {q} parameter is queue which stores childs to be visited in bfs
   for(int node=start;node<=end;node++)          // running loop from starting node to end node
   {
      if(vis[node])continue;      // if node is visted means its component in graph has been calculted so we continue loop
      else components++;          // else we increase the no. of components by one and move further    
      int cur=node;               // {cur} is current node which is processing in bfs and we initilize it as node which is unvisited
      q.push(cur);                  //pushing into queue for bfs
      vis[cur]=1;                    // mark node visited so we will not process it later
      while(!q.empty())             // running bfs loop
      {
         cur=q.front();            // extracting data of front node from queue
         q.pop();                  // removing front node
         for(auto child:adj[cur]) if(!vis[child])    //{child} is child of current node which is processing under bfs and check if child is not visited
         {
            q.push(child);               // pushing non visited node in queue
            vis[child]=1;                // marking it as visited
         }
      }
   }
   return components;                   // returning components in graph
}

/**
 * @brief Main function
 * @returns 0 on exit
 */

int main()
{
   int nodes,edges;                    // {nodes} is no. of nodes and {edges} are no. of edges which will given in question as input
   std::cin>>nodes>>edges;                  // taking input
   std::vector<std::vector<int>>adj(nodes+1);    // declaring adjacency list for graph and assigning its size as of no. of nodes and adding one to it such that we have access to last number node 
   for(int i=1;i<=edges;i++)           // running loop for taking input
   {
      int node_a,node_b;              
      std::cin>>node_a>>node_b;             // taking input for edge
      adj[node_a].push_back(node_b);   // pushing into graph as bidirectional edge
      adj[node_b].push_back(node_a);
   }

   int connected_components;             // declaring connected_components which stores answer
   connected_components=connected_components_bfs(adj,nodes);   // calling function
   std::cout<<connected_components<<std::endl;                   // printing answer
   return 0;   // exiting main function
}

