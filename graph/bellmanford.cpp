#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <ratio>
#include <thread>
using namespace std;

struct Edge
{
    int u;
    int v;
    int w;
};
struct Graph
{
    int V;
    int E;
    vector<Edge> edges;
};

struct Graph *createGraph(int V)
{
    struct Graph *graph = new Graph;
    graph->V = V;
    return graph;
}

void printResult(int dis[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        cout << "\nShortest path to " << i + 1 << ": cost = " << dis[i];
    }
    cout << "\n";
}

void BellmanFord(struct Graph *graph, int u)
{
    int V = graph->V;
    int E = graph->E;
    int dist[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
    }

    dist[u] = 0;

    for (int i = 1; i <= V - 1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph->edges[j].u;
            int v = graph->edges[j].v;
            int w = graph->edges[j].w;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    for (int i = 0; i < E; i++)
    {
        int u = graph->edges[i].u;
        int v = graph->edges[i].v;
        int w = graph->edges[i].w;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v])
        {
            cout << "\nGraph contains negative w cycle.\n";
            return;
        }
    }

    printResult(dist, V);

    return;
}

int main()
{
    int vertices, edgeCount = 0;
    struct Graph *graph;
    vector<string> listOfLines;
    vector<int> listOfedges;
    string text,filename;
    cout << "\n***Please provide filename from following options:***";
    cout << "\nfilename_10_data.txt\tfilename_100_data.txt\tfilename_500_data.txt\tfilename_1000_data.txt\tfilename_negetive_weight.txt\n>> ";
    cin >> filename;
    cout << "\nyou have given file name: "<< filename;
    ifstream inputFile(filename);
    while (getline(inputFile, text))
    {
        listOfLines.push_back(text);
    }
    inputFile.close();

    for (int i = 0; i < listOfLines.size(); i++)
    {
        if (i == 0)
        {
            vertices = stoi(listOfLines[0]);
            graph = createGraph(vertices);
        }
        else
        {
            stringstream ss(listOfLines[i]);
            string word;
            while (!ss.eof())
            {
                getline(ss, word, ' ');
                listOfedges.push_back(stoi(word));
            }
            for (int k = 1; k < listOfedges.size(); k = k + 2)
            {

                cout << "\nindex:: [" << listOfedges[0] << "] [" << listOfedges[k] << "] value:: " << listOfedges[k + 1];
                Edge edge;
                edge.u = listOfedges[0] - 1;
                edge.v = listOfedges[k] - 1;
                edge.w = listOfedges[k + 1];
                graph->edges.push_back(edge);
                cout << "\n\n";
            }
            listOfedges.clear();
        }
    }
    int startNode = 0;
    graph->E = graph->edges.size();
    clock_t start, stop;
    start = clock();
    BellmanFord(graph, startNode);
    stop = clock();
    double time_taken = double(stop - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(8);
    cout << " sec " << endl;
    return 0;
}