#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

int n, m, graph[505][505], x, y;
int visited[505];
int shortest[505];
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> x >> y;
		graph[x][y] = 1;
		graph[y][x] = 1;
	}
	for (int i = 1; i <= n; i++) graph[i][i] = 1;
	//下面只要是0的边就是补图上的边
	//bfs
	visited[1] = 1;//从1开始
	queue<int>que;
	que.push(1);
	int step = 0;
	//bfs
	while (!que.empty())
	{
		step++;
		int size = que.size();
		while (size) {
			int u = que.front();
			que.pop();
			for (int j = 1; j <= n; j++) {
				if (graph[u][j] == 0 && !visited[j]) {
					int v = j;
					que.push(v);
					visited[v] = 1;
					shortest[v] = step;
				}
			}
			size--;
		}
	}
	for (int j = 2; j <= n; j++) cout << shortest[j] << ' ';
	return 0;
}