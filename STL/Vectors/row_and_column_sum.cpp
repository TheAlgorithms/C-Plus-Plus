
void row_sum(vector<vector<int>> arr, int n, int m, vector<int> &row)
{
    int i, j, sum = 0;
    for (i = 0; i < m; ++i)
    {
        for (j = 0; j < n; ++j)
            sum = sum + arr[i][j];

        row.push_back(sum);
        sum = 0;
    }
}
void column_sum(vector<vector<int>> arr, int n, int m, vector<int> &column)
{
    int i, j, sum = 0;
    for (i = 0; i < m; ++i)
    {
        for (j = 0; j < n; ++j)
            sum = sum + arr[j][i];

        column.push_back(sum);
        sum = 0;
    }
}