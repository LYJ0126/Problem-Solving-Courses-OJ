#include<iostream>
using namespace std;

int n, m, i, j, mini, u, v, w;
int e[1002][1002], dis[1002], check[1002];
const int wq = 0x7fffffff;
int num = 1, sum = 0;
int main()
{
	cin >> n >> m;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
		{
			if (i == j) e[i][j] = 0;
			else e[i][j] = wq;
		}

	for (i = 1; i <= m; i++)
	{
		cin >> u >> v >> w;
		e[u][v] = w;
		e[v][u] = w;
	}

	for (i = 1; i <= n; i++)
		dis[i] = e[1][i];

	check[1] = 1;
	while (num <= n - 1)
	{
		mini = wq;
		for (i = 1; i <= n; i++)
		{
			if (check[i] == 0 && dis[i] < mini)
			{
				mini = dis[i];
				j = i;
			}
		}
		sum += mini;
		num++;
		check[j] = 1;
		for (int k = 1; k <= n; k++)
		{
			if (check[k] == 0 && dis[k] > e[j][k])
			{
				dis[k] = e[j][k];
			}
		}
	}

	cout << sum;
	return 0;
}