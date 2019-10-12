void FloydWarshall(int n)
{
	// 1 indexed
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			dist[i][j] = graph[i][j]; 
		}
	}
	for(int k = 1; k <= n; k++)
	{
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
}
