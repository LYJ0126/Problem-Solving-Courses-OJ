#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

typedef long long ll;
int n, m, x, y;
ll w, ans = 0x7fffffffff;
ll graph[201][201];
ll dis[201][201];
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (i != j) graph[i][j] = dis[i][j] = 0x7fffffffff;
		}
	}
	for (int i = 0; i < m; ++i) {
		scanf("%d%d%lld", &x, &y, &w);
		graph[x][y] = min(graph[x][y], w);
		graph[y][x] = min(graph[y][x], w);
		dis[x][y] = min(dis[x][y], w);
		dis[y][x] = min(dis[y][x], w);
	}
	//floyd
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i < k; ++i) {
			for (int j = i + 1; j < k; ++j) {
				ans = min(ans, dis[i][j] + graph[i][k] + graph[k][j]);
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
				dis[j][i] = dis[i][j];
			}
		}
	}
	if (ans == 0x7fffffffff) printf("-1");
	else printf("%lld", ans);
	return 0;
}