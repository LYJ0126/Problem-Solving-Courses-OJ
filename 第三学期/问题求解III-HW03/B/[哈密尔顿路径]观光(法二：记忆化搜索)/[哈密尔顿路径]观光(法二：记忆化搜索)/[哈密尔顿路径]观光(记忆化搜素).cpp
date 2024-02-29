#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int n, m, x, y, w;
vector<vector<int>>graph;
vector<vector<int>>dp;
int dfs(int state, int v)
{
	if (dp[state][v] < 99999999) return dp[state][v];//记忆化搜索
	int temp = 99999999, formerstate = state ^ (1 << v);
	for (int u = 0; u < n; u++) {
		if (u == v) continue;
		if (graph[u][v] == 99999999) continue;//没有边
		if (!((formerstate >> u) & 1)) continue;//上一个状态不包含点u
		temp = min(temp, dfs(formerstate, u) + graph[u][v]);//向下递归找子问题
	}
	dp[state][v] = temp;//记忆化
	return temp;
}
int main()
{
	cin >> n >> m;
	int len = (1 << n) - 1;
	graph.resize(n, vector<int>(n, 99999999));
	dp.resize(len + 1, vector<int>(n, 99999999));
	for (int i = 0; i < m; i++) {
		cin >> x >> y >> w;
		graph[x - 1][y - 1] = graph[y - 1][x - 1] = min(graph[x - 1][y - 1], w);//注意！可能有重边
	}
	for (int x = 0; x < n; x++) dp[1 << x][x] = 0;
	int res = 0x3f3f3f3f;
	for (int i = 0; i < n; i++) {
		res = min(res, dfs(len, i));
	}
	if (res == 99999999) cout << -1;
	else cout << res;
	return 0;
}