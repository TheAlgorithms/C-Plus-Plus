#include <iostream>
#include <fstream>
#define max 100
using namespace std;

int main()
{

  int u, v, w;
  int x;
  cout << "enter the number of vertices -TYPE 5 IF USING MY GIVEN INPUT FILE" << endl;
  cin >> x;
  ifstream myfile("input.txt");

  int graph[x][x];
  //////////////////////////////////////////////
  //intitailising graph matrix
  for (int i = 0; i < x; i++)
  {
    for (int j = 0; j < x; j++)
    {
      graph[i][j] = 1000000;
    }
    cout << endl;
  }

  //////////////////////////////////////////
  ///taking input from text file
  while (!myfile.eof())
  {
    myfile >> u;
    myfile >> w;
    myfile >> v;
    graph[u - 1][v - 1] = w;
  }
  /////////////////////////////////////////////
  //display input graph
  for (int i = 0; i < x; i++)
  {
    for (int j = 0; j < x; j++)
    {
      if (i == j)
      {
        graph[i][j] = 0;
      }
      cout << graph[i][j] << "\t";
    }
    cout << endl;
  }
  ///////////////////////////////////////////////////
  int p[x][x]; //precedance matrix
  for (int i = 0; i < x; i++)
  {
    for (int j = 0; j < x; j++)
    {
      p[i][j] = i;
    }
  }
  ///////////////////////////////////////
  //algorrithm
  for (int k = 0; k < x; k++)
  {
    for (int i = 0; i <= x; i++)
    {
      for (int j = 0; j < x; j++)
      {
        if (graph[i][k] + graph[k][j] < graph[i][j])
        {
          graph[i][j] = graph[i][k] + graph[k][j];
          p[i][j] = p[k][j];
        }
      }
    }
  }
  ///////////////////////////////////////////////
  //display result
  cout << "the distance matrix is " << endl;
  for (int i = 0; i < x; i++)
  {
    for (int j = 0; j < x; j++)
    {
      cout << graph[i][j] << "\t";
    }
    cout << endl;
  }

  cout << endl
       << endl
       << endl
       << "the precedance matrinx is" << endl;
  for (int i = 0; i < x; i++)
  {
    for (int j = 0; j < x; j++)
    {
      cout << p[i][j] + 1 << "\t";
    }
    cout << endl;
  }

  return 0;
}