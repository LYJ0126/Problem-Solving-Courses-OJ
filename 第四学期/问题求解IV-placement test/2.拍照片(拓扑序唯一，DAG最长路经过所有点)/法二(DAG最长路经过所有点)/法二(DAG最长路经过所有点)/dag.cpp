#include<iostream>
#include<cstring>
#include<vector>
#include<cmath>
#include<queue>
#include<unordered_map>
using namespace std;

int T, n, m;
typedef long long ll;
vector<vector<int>>graph;
vector<int>indeg;//入度
vector<bool>vis;
unordered_map<int, ll>edge;//记录边权(0表示没有边，1表示有边)
vector<int>dp;
int DP(int u) {//记忆化搜索找最长路径长度,以最矮的人为起点
	if (vis[u]) return dp[u];
	vis[u] = true;
	for (int v : graph[u]) {
		if (edge[u << 18 | v]) dp[u] = max(dp[u], DP(v) + 1);//以u为起点最长路和u->v路+以v为起点最长路，二者取最大
	}
	return dp[u];
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while (T--) {
		cin >> n >> m;
		graph.clear();
		graph.resize(n + 1);
		indeg.clear();
		indeg.resize(n + 1, 0);
		vis.clear();
		vis.resize(n + 1, false);
		edge.clear();
		int a, b;
		for (int i = 0; i < m; ++i) {
			cin >> a >> b;
			graph[a].push_back(b);//a->b
			++indeg[b];
			edge[(a << 18) | b] = 1;//记录a->b的边权,1表示有边。因为数据范围是1e5,所以用移位操作加哈希表记录边权
		}
		int lowest = 0;//最矮的人
		for (int i = 1; i <= n; ++i) {
			if (!indeg[i]) {
				if(!lowest)lowest = i;
				else {//有多个最矮的人
					lowest = 0;
					break;
				}
			}
		}
		if (!lowest) {//没有最矮的人或者有多个最矮的人
			cout << "NO" << '\n';
			continue;
		}
		//通过拓扑排序判断是否有环
		queue<int>que;
		que.push(lowest);
		while (!que.empty()) {
			int u = que.front();
			que.pop();
			vis[u] = true;
			for (int v : graph[u]) {
				--indeg[v];
				if (!indeg[v]) {
					que.push(v);
				}
			}
		}
		//判断是否无环且连通
		bool flag = true;
		for (int i = 1; i <= n; ++i) {
			if (indeg[i] || !vis[i]) {
				flag = false;
				break;
			}
		}
		if (!flag) {//有环或者不连通
			cout << "NO" << '\n';
			continue;
		}
		//判断最长路长度是否为n-1
		//dp
		dp.clear();
		for (int i = 1; i < n; ++i) vis[i] = false;
		dp.resize(n + 1, 0);
		if (DP(lowest) != n - 1) {//最长路长度不为n-1
			cout << "NO" << '\n';
			continue;
		}
		cout << "YES" << '\n';
	}
	return 0;
}