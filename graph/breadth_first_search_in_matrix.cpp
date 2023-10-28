// The aim of the breadth first search in a matrix is to tell whether a path
// exists or not and in how many steps we can reach them
#include <bits/stdc++.h>
using namespace std;

void breadth_first_search(vector<vector<int>> matrix, int source_x,
                          int source_y, int destination_x, int destination_y) {
    int count =
        0;  // counting the number of steps from the source to the destination
    int row_index, column_index;
    map<pair<int, int>, pair<int, int>> parent;
    pair<int, int> p;
    // The map is used to store the child as key and parent as value it is like
    // a hierachy level the in usual breadth first it does the level by level
    // search
    //  so that the parent is above the children which means the the children is
    //  visited through the node.
    // And also the map is used to show the path construction.
    map<pair<int, int>, pair<int, int>>::iterator it;
    parent[{source_x, source_y}] = {-1, -1};
    if (matrix[source_x][source_y] == 2) {
        cout << "The source and destination have the smae coordinates.";
        return;
    }
    queue<pair<int, int>> q;
    // for adding the coordinates the child nodes that are visited by the parent
    // node zero means the node is unvisited and 3 means the node is visited
    q.push({source_x, source_y});
    // Initially the queue is empty and after that the source is added in order
    // to start at that node
    while (q.size() != 0) {
        row_index = q.front().first;      // retriving the row index
        column_index = q.front().second;  // retriving the column
        q.pop();
        // removing the head of the queue
        if (row_index - 1 >= 0 and row_index - 1 <= matrix.size() - 1 and
            column_index >= 0 and column_index <= matrix[0].size() - 1 and
            matrix[row_index - 1][column_index] == 0) {
            matrix[row_index - 1][column_index] = 3;  // setting as visited
            q.push({row_index - 1, column_index});
            parent[{row_index - 1, column_index}] = {row_index, column_index};
        } else if (row_index - 1 >= 0 and row_index - 1 <= matrix.size() - 1 and
                   column_index >= 0 and
                   column_index <= matrix[0].size() - 1 and
                   matrix[row_index - 1][column_index] == 2) {
            parent[{row_index - 1, column_index}] = {row_index, column_index};
            break;
        }
        if (row_index >= 0 and row_index <= matrix.size() - 1 and
            column_index + 1 >= 0 and
            column_index + 1 <= matrix[0].size() - 1 and
            matrix[row_index][column_index + 1] == 0) {
            matrix[row_index][column_index + 1] = 3;  // setting as visited
            q.push({row_index, column_index + 1});
            parent[{row_index, column_index + 1}] = {row_index, column_index};
        } else if (row_index >= 0 and row_index <= matrix.size() - 1 and
                   column_index + 1 >= 0 and
                   column_index + 1 <= matrix[0].size() - 1 and
                   matrix[row_index][column_index + 1] == 2) {
            parent[{row_index, column_index + 1}] = {row_index, column_index};
            break;
        }
        if (row_index + 1 >= 0 and row_index + 1 <= matrix.size() - 1 and
            column_index >= 0 and column_index <= matrix[0].size() - 1 and
            matrix[row_index + 1][column_index] == 0) {
            matrix[row_index + 1][column_index] = 3;  // setting as visited
            q.push({row_index + 1, column_index});
            parent[{row_index + 1, column_index}] = {row_index, column_index};
        } else if (row_index + 1 >= 0 and row_index + 1 <= matrix.size() - 1 and
                   column_index >= 0 and
                   column_index <= matrix[0].size() - 1 and
                   matrix[row_index + 1][column_index] == 2) {
            parent[{row_index + 1, column_index}] = {row_index, column_index};
            break;
        }
        if (row_index >= 0 and row_index <= matrix.size() - 1 and
            column_index - 1 >= 0 and
            column_index - 1 <= matrix[0].size() - 1 and
            matrix[row_index][column_index - 1] == 0) {
            matrix[row_index][column_index - 1] = 3;  // setting as visited
            q.push({row_index, column_index - 1});
            parent[{row_index, column_index - 1}] = {row_index, column_index};
        } else if (row_index >= 0 and row_index <= matrix.size() - 1 and
                   column_index - 1 >= 0 and
                   column_index - 1 <= matrix[0].size() - 1 and
                   matrix[row_index][column_index - 1] == 2) {
            parent[{row_index, column_index - 1}] = {row_index, column_index};
            break;
        }
    }
    // path construction showing the path from the destination to the source
    cout << "Path Construction";
    int path_x, path_y;
    path_x = destination_x;
    path_y = destination_y;
    while (path_x != -1 and path_y != -1) {
        cout << path_x << " " << path_y << "\n";
        // cout<<parent[{path_x,path_y}].first<<"
        // "<<parent[{path_x,path_y}].second<<"\n";
        p = parent[{path_x, path_y}];
        path_x = p.first;
        path_y = p.second;
        count++;
    }
    cout << "The number of steps to reach from the source to destinstion is:"
         << count - 1;
    // cout<<"\n";
    // for(int i=0;i<matrix.size();i++)
    // {
    //     for(int j=0;j<matrix[i].size();j++)
    //     {
    //         cout<<matrix[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // for(it=parent.begin();it!=parent.end();it++)
    // {
    //     cout<<(*it).first.first<<" "<<(*it).first.second<<" ->
    //     "<<(*it).second.first<<" "<<(*it).second.second<<"\n";
    // }
}

int main() {
    // getting input for setting the rows and columns of the matrix it is based
    // on 0 indexed
    int rows, columns;
    cout << "Enter the rows:";
    cin >> rows;
    cout << "Enter the columns:";
    cin >> columns;
    vector<vector<int>> v(rows, vector<int>(columns, 0));  // setting the matrix
    // by the way the vector set default value as zero
    // getting the source
    int source_x, source_y, destination_x, destination_y;
    cout << "Enter the coordinates for the source:";
    cin >> source_x >> source_y;
    cout << "Enter the coordinates for the destination:";
    cin >> destination_x >> destination_y;
    // If you give row and columns as m and n then you have to give the start
    // and destination position from (0,0) to (m-1,n-1) anything other than that
    // would not acceptable.
    if (source_x >= 0 and source_x <= rows - 1 and source_y >= 0 and
        source_y <= columns - 1 and destination_x >= 0 and
        destination_x <= rows - 1 and destination_y >= 0 and
        destination_y <= columns - 1) {
        v[source_x][source_y] = 1;            // for denoting source
        v[destination_x][destination_y] = 2;  // for denoting destination
        // the rest of the blocks in the matrix will set as zero
        breadth_first_search(v, source_x, source_y, destination_x,
                             destination_y);
    }
}
